#include "SWGVRCharacter.h"

#include "IHeadMountedDisplay.h"
#include "IXRTrackingSystem.h"
#include "FileHelper.h"

#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "MotionControllerComponent.h"
#include "SWGVRCameraLocator.h"
#include "SWGVRPlayerControllerBase.h"
#include "SWGVRUtil.h"
#include "Engine/Engine.h"

#include "GameFramework/WorldSettings.h"
#include "Kismet/GameplayStatics.h"

#define NEW_INFINITY ((float)(_HUGE_ENUF * _HUGE_ENUF))

ASWGVRCharacter::ASWGVRCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	LeftGrabActionName = "LeftGrab";
	RightGrabActionName = "RightGrab";

	ThrowMagnitude = 1.f;
	bGrabClosest = true;
	HandsThatInteract = EVRHandType::Both;

	LeftInteractActionName = "LeftInteract";
	RightInteractActionName = "RightInteract";

	bUseEyeOffsetForEyeTracking = true;
	EyeOffset = 100.f;

	bUseHandForPad = false;
	HandToUseAsPad = EVRHandType::Right;

	PadLineTraceDistance = 100.f;
	LerpGrabSpeed = 1000.f;

	bPerfCounterEnabled = true;

	FPSMin = NEW_INFINITY; // New infinity
	FPSMax = -NEW_INFINITY; // New infinity

	FPSAverageOverTime = 0.f;
	PerfCounterSeconds = 0.f;
	TotalPerfSeconds = 0.f;

	VRModeEnabled = true;
	WasPreviouslyInVR = true;

	LeftController.ClosestGrabbableActor = nullptr;
	LeftController.ClosestGrabbableDistance = NEW_INFINITY;
	LeftController.ClosestHoveredActor = nullptr;
	LeftController.ClosestHoveredComponent = nullptr;
	LeftController.ClosestDistance = NEW_INFINITY;
	LeftController.bIsTracked = false;

	RightController.ClosestGrabbableActor = nullptr;
	RightController.ClosestGrabbableDistance = NEW_INFINITY;
	RightController.ClosestHoveredActor = nullptr;
	RightController.ClosestHoveredComponent = nullptr;
	RightController.ClosestDistance = NEW_INFINITY;
	RightController.bIsTracked = false;

	bIsUsingPadForHand = false;
	m_previousWorldToMeters = 100.f;

	NonVROffset = FVector::ZeroVector;
	bUseNonVROffset = false;

	VROriginComp = CreateDefaultSubobject<USceneComponent>("VRCameraOrigin");
	VROriginComp->SetupAttachment(GetRootComponent());

	VRCameraAdjuster = CreateDefaultSubobject<USceneComponent>("VRCameraAdjuster");
	VROriginComp->SetupAttachment(VROriginComp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(VRCameraAdjuster);

	LeftHandComponent = CreateDefaultSubobject<UMotionControllerComponent>("LeftHand");
	LeftHandComponent->SetupAttachment(VRCameraAdjuster);
	LeftHandComponent->SetTrackingSource(EControllerHand::Left);

	LeftHandTrigger = CreateDefaultSubobject<USphereComponent>("LeftHandTrigger");
	LeftHandTrigger->SetupAttachment(LeftHandComponent);

	LeftAttachPoint = CreateDefaultSubobject<USphereComponent>("LeftAttachPoint");
	LeftAttachPoint->SetupAttachment(LeftHandComponent);

	RightHandComponent = CreateDefaultSubobject<UMotionControllerComponent>("RightHand");
	RightHandComponent->SetupAttachment(VRCameraAdjuster);
	RightHandComponent->SetTrackingSource(EControllerHand::Right);

	RightHandTrigger = CreateDefaultSubobject<USphereComponent>("RightHandTrigger");
	RightHandTrigger->SetupAttachment(RightHandComponent);

	RightAttachPoint = CreateDefaultSubobject<USphereComponent>("RightAttachPoint");
	RightAttachPoint->SetupAttachment(RightHandComponent);

	PadMotionComponent = CreateDefaultSubobject<UMotionControllerComponent>("PadMotion");
	PadMotionComponent->SetupAttachment(VRCameraAdjuster);

	PadAttachPoint = CreateDefaultSubobject<USceneComponent>("PadAttachPoint");
	PadAttachPoint->SetupAttachment(PadMotionComponent);

	PadInteractionPointer = CreateDefaultSubobject<UArrowComponent>("PadInteractionPointer");
	//PadInteractionPointer->SetupAttachment(PadMotionComponent); --- They do not do this? so they do not attach this arrow to anything?
}

void ASWGVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckPSVRHandStatus();

	if (IsInVRMode())
	{
		float WorldToMeters = GetWorld()->GetWorldSettings()->WorldToMeters;
		if (WorldToMeters != m_previousWorldToMeters)
		{
			m_previousWorldToMeters = WorldToMeters;
			FVector NewLocation = VRCameraAdjuster->GetComponentLocation();
			NewLocation.Z = (WorldToMeters * 0.0099999998) * EyeOffset;

			VRCameraAdjuster->SetRelativeLocationAndRotation(NewLocation, VRCameraAdjuster->GetComponentRotation());
		}
	}

	if (USWGVRUtil::GetPlayType() == EVRPlayType::NotUsingVR)
	{
		if (LeftHandComponent->GetAttachParent() != CameraComp)
		{
			LeftHandComponent->AttachToComponent(CameraComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			LeftHandComponent->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
		}

		if (RightHandComponent->GetAttachParent() != CameraComp)
		{
			RightHandComponent->AttachToComponent(CameraComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			RightHandComponent->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
		}
	}
	else
	{
		ProcMotionController(EVRHandType::Left, LeftHandComponent, LeftController, LeftAttachPoint);
	}

	ProcMotionController(EVRHandType::Right, RightHandComponent, RightController, RightAttachPoint);

	if (bPerfCounterEnabled)
	{
		int ImmediateSeconds = DeltaTime + PerfCounterImmediateSeconds;
		int NewAverageFrameCounter = FrameCounterForAverage + 1;

		FrameCounterForAverage = NewAverageFrameCounter;
		PerfCounterImmediateSeconds = ImmediateSeconds;
		if (ImmediateSeconds >= 1.0)
		{
			PerfCounterImmediateSeconds = 0.0;
			FPSImmediate = 1.0 / DeltaTime;
		}
		float Seconds = DeltaTime + PerfCounterSeconds;
		float TimeStamp = DeltaTime + TotalPerfSeconds;

		PerfCounterSeconds = Seconds;
		TotalPerfSeconds = TimeStamp;

		if (Seconds >= 5.0)
		{
			FrameCounterForAverage = 0;
			PerfCounterSeconds = 0.0;

			float FPS = NewAverageFrameCounter / Seconds;
			FPSAverageOverTime = FPS;

			FPerformanceInfo PerfInfo;
			PerfInfo.TimeStamp = TimeStamp;
			PerfInfo.FPS = FPS;

			PerformanceList.Add(PerfInfo);
		}
	}
}

void ASWGVRCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	BindGrabActions(PlayerInputComponent, EVRHandType::Left, LeftGrabActionName);
	BindGrabActions(PlayerInputComponent, EVRHandType::Right, RightGrabActionName);
	BindInteractionActions(PlayerInputComponent, EVRHandType::Left, LeftInteractActionName);
	BindInteractionActions(PlayerInputComponent, EVRHandType::Right, RightInteractActionName);
}

void ASWGVRCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	StopFrameCounters();
}

void ASWGVRCharacter::OnUsingGamepadChanged(bool gamepad)
{
	// Possibly inlined elsewhere
}

void ASWGVRCharacter::BeginPlay()
{
	if (GEngine && GEngine->XRSystem.IsValid())
	{
		IHeadMountedDisplay* CurrentHMD = GEngine->XRSystem->GetHMDDevice();
		CurrentHMD->EnableHMD(CurrentHMD->IsHMDConnected());

		TSharedPtr<IStereoRendering, ESPMode::ThreadSafe> StereoRendering = GEngine->XRSystem->GetStereoRenderingDevice();
		if (StereoRendering.IsValid())
			StereoRendering->EnableStereo(CurrentHMD->IsHMDConnected());

		FName HMDSystemName = GEngine->XRSystem->GetSystemName();
		if (HMDSystemName == "PSVR" || HMDSystemName == "OculusHMD")
		{
			VRTrackingOrigin = EHMDTrackingOrigin::Eye;
		}

		GEngine->XRSystem->SetTrackingOrigin(VRTrackingOrigin);
		USWGVRUtil::ChangePlayType((!CurrentHMD->IsHMDConnected() ? EVRPlayType::NotUsingVR : EVRPlayType::UsingVR));
	}
	else
	{
		USWGVRUtil::ChangePlayType(EVRPlayType::NotUsingVR);
	}

	TArray<AActor*> CameraLocators;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASWGVRCameraLocator::StaticClass(), CameraLocators); // They can just used GetActorOfClass probably for just the first one
	if (CameraLocators.Num() > 0)
	{
		AActor* CameraLocator = CameraLocators[0];

		FVector LocationToUse = FVector::ZeroVector;
		if (CameraLocator->GetRootComponent())
		{
			LocationToUse = CameraLocator->GetRootComponent()->GetComponentLocation();
		}

		FRotator RotationToUse = FRotator::ZeroRotator;
		if (CameraLocator->GetRootComponent())
		{
			RotationToUse = CameraLocator->GetRootComponent()->GetComponentRotation();
		}

		// TODO: Double check
		SetActorLocationAndRotation(LocationToUse, RotationToUse);
	}

	if (USWGVRUtil::GetPlayType() == EVRPlayType::NotUsingVR && bUseNonVROffset)
	{
		SetCameraWorldLocation(NonVROffset);
	}
	else if ((VRTrackingOrigin == EHMDTrackingOrigin::Eye || USWGVRUtil::GetPlayType() == EVRPlayType::NotUsingVR) && bUseEyeOffsetForEyeTracking)
	{
		FVector NewLocation = {}; // TODO: Double check
		NewLocation.Z = (m_previousWorldToMeters * 0.0099999998) * EyeOffset;

		VRCameraAdjuster->SetRelativeLocationAndRotation(NewLocation, VRCameraAdjuster->GetComponentRotation());
	}

	LeftHandTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASWGVRCharacter::OnLeftBeginOverlap);
	LeftHandTrigger->OnComponentEndOverlap.AddDynamic(this, &ASWGVRCharacter::OnLeftEndOverlap);

	RightHandTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASWGVRCharacter::OnRightBeginOverlap);
	RightHandTrigger->OnComponentEndOverlap.AddDynamic(this, &ASWGVRCharacter::OnRightEndOverlap);

	Super::BeginPlay();
}

void ASWGVRCharacter::CheckPSVRHandStatus()
{
	if (GEngine && GEngine->XRSystem.IsValid())
	{
		FName SystemName = GEngine->XRSystem->GetSystemName();

		if (SystemName == "PSVR")
			VRTrackingOrigin = EHMDTrackingOrigin::Eye;
	}
}

void ASWGVRCharacter::RemoveDestroyedActor(FMotionControllerInfo& ControllerInfo, AActor* DestroyedActor)
{
}

void ASWGVRCharacter::SendOnHoverBeginEvents(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             EVRHandType Hand, FMotionControllerInfo& ControllerInfo)
{
}

void ASWGVRCharacter::SendOnHoverEndEvents(AActor* OtherActor, EVRHandType Hand, FMotionControllerInfo& ControllerInfo)
{
}

void ASWGVRCharacter::OnGrabAction(EVRHandType Hand)
{
}

void ASWGVRCharacter::OnReleaseAction(EVRHandType Hand)
{
}

void ASWGVRCharacter::BindGrabActions(class UInputComponent* PlayerInputComponent, EVRHandType Hand, FName ActionName)
{
}

bool ASWGVRCharacter::ReleaseGrabbableInternal(AActor* Grabbable, EVRHandType Hand, bool bForce,
	const FVector& Velocity, FMotionControllerInfo* ControllerInfo)
{
	return false;
}

void ASWGVRCharacter::OnInteractAction(EVRHandType Hand)
{
}

void ASWGVRCharacter::SendOnVRInteract(UObject* Object, EVRHandType Hand)
{
}

void ASWGVRCharacter::BindInteractionActions(UInputComponent* PlayerInputComponent, EVRHandType Hand, FName ActionName)
{
}

void ASWGVRCharacter::ChangeHoveredActor(AActor*& CurrentHoveredActor, UPrimitiveComponent*& CurrentHoveredComponent,
                                         AActor* newHoverActor, UPrimitiveComponent* newHoverComponent,
                                         EVRHandType Hand)
{
}

void ASWGVRCharacter::ProcMotionController(EVRHandType Hand, USceneComponent* ProcMotionController,
                                           FMotionControllerInfo& ControllerInfo, USceneComponent* AttachPoint)
{
}

void ASWGVRCharacter::FindClosestActor(FVector CurrentLocation, float& closestDist, AActor*& closestActor,
                                       TArray<AActor*>& actorList)
{
}

void ASWGVRCharacter::StopFrameCounters()
{
	if (bPerfCounterEnabled)
	{
		bPerfCounterEnabled = false;

		FString result = TEXT("Time,FPS\n");

		for (int i = 0; i != PerformanceList.Num(); i++)
		{
			FPerformanceInfo PerfInfo = PerformanceList[i];
			FString PerfString = FString::Printf(TEXT("%f,%f\n"), PerfInfo.TimeStamp, PerfInfo.FPS);
			// Why isn't this using timestamp as a datetime, that's probably more readable

			result += result.Append(PerfString);
		}
		FDateTime TimeNow = FDateTime::Now();

		// They should really use GetNameSafe here not just GetName, this also only allows one of these per minute as it replaces the old
		FString PerfOutput = FString::Printf(TEXT("%s/Performance/%s_%d%.2d%.2d_%.2d%.2d_fps.txt"),
		                                     *FPaths::ProjectLogDir(), *GetWorld()->GetName(), TimeNow.GetYear(),
		                                     TimeNow.GetMonth(), TimeNow.GetDay(), TimeNow.GetHour(),
		                                     TimeNow.GetMinute());

		FFileHelper::SaveStringToFile(result, *PerfOutput);
	}
}

void ASWGVRCharacter::StartFrameCounters()
{
	if (!bPerfCounterEnabled)
	{
		bPerfCounterEnabled = true;
		TotalPerfSeconds = 0;
		PerfCounterSeconds = 0.0;
	}
}

void ASWGVRCharacter::SetVRModeEnabled(bool enable)
{
	VRModeEnabled = enable;
}

void ASWGVRCharacter::SetHeldOffset(EVRHandType Hand, const FVector& NewOffset, int32 ItemIndex)
{
}

void ASWGVRCharacter::SetCameraWorldRotation(const FRotator& Rotation)
{
}

void ASWGVRCharacter::SetCameraWorldLocationAndRotation(const FVector& Location, const FRotator& Rotation)
{
}

void ASWGVRCharacter::SetCameraWorldLocation(const FVector& Location)
{
	FVector Offset = {};
	Offset.X = Location.X;
	Offset.Y = Location.Y;
	Offset.Z = Location.Z;

	VRCameraAdjuster->SetWorldLocation(Offset);
	EyeOffset = Location.Y;
	bUseNonVROffset = true;
}

void ASWGVRCharacter::SetCameraRelativeRotation(const FRotator& Rotation)
{
}

void ASWGVRCharacter::SetCameraRelativeLocationAndRotation(const FVector& Location, const FRotator& Rotation)
{
}

void ASWGVRCharacter::SetCameraRelativeLocation(const FVector& Location)
{
}

void ASWGVRCharacter::ReleaseGrabbable(AActor* Grabbable, bool bForce, bool bOverrideVelocity, FVector Velocity)
{
}

void ASWGVRCharacter::ReleaseAll(EVRHandType Hand, bool bForce, bool bOverrideVelocity, FVector Velocity)
{
	// inaccurate, game uses "&" idk why
	if (Hand == EVRHandType::Right)
	{
		// todo maybe not copy here
		TArray<AActor*> grabbableList = RightController.HeldGrabbables;
		for (AActor* Grabbable : grabbableList)
		{
			ReleaseGrabbable(Grabbable, bForce, bOverrideVelocity, Velocity);
		}
	}
	
	// inaccurate, game uses "&" idk why
	if (Hand == EVRHandType::Left)
	{
		// todo maybe not copy here
		TArray<AActor*> grabbableList = LeftController.HeldGrabbables;
		for (AActor* Grabbable : grabbableList)
		{
			ReleaseGrabbable(Grabbable, bForce, bOverrideVelocity, Velocity);
		}
	}
}

void ASWGVRCharacter::ProcessInterpolatedGrab_Implementation(const FTransform& AttachmentTransform,
                                                             FHeldGrabbableInfo& ActorGrabbablePair, AActor* HeldActor,
                                                             EVRHandType Hand)
{
	FVector FinalLoc = AttachmentTransform.TransformPosition(ActorGrabbablePair.AttachmentRelativeLocation);
	FVector InterpLoc = FMath::VInterpConstantTo(HeldActor->GetActorLocation(),
		FinalLoc, GetWorld()->DeltaTimeSeconds, LerpGrabSpeed);

	FQuat Rot= AttachmentTransform.TransformRotation(ActorGrabbablePair.AttachmentRelativeRotation.Quaternion());
	SetActorLocationAndRotation(InterpLoc, Rot);

	if (FVector::PointsAreNear(InterpLoc, FinalLoc, 1.0f))
	{
		ActorGrabbablePair.IsLerpingToHand = false;
	}
}

void ASWGVRCharacter::OnTrackedControllerChanged_Implementation()
{
	// nullsub
}

void ASWGVRCharacter::OnRightEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SendOnHoverEndEvents(OtherActor, EVRHandType::Right, RightController);
}

void ASWGVRCharacter::OnRightBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                          const FHitResult& SweepResult)
{
	SendOnHoverBeginEvents(OverlappedComponent, OtherActor, EVRHandType::Right, RightController);
}

void ASWGVRCharacter::OnRelease_Implementation(AActor* Grabbable, EVRHandType Hand)
{
	// nullsub
}

void ASWGVRCharacter::OnLeftEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SendOnHoverEndEvents(OtherActor, EVRHandType::Left, LeftController);
}

void ASWGVRCharacter::OnLeftBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                         const FHitResult& SweepResult)
{
	SendOnHoverBeginEvents(OverlappedComponent, OtherActor, EVRHandType::Left, LeftController);
}

void ASWGVRCharacter::OnHoverEnd_Implementation(AActor* HoveredActor, EVRHandType Hand)
{
	// nullsub
}

void ASWGVRCharacter::OnHoverBegin_Implementation(AActor* HoveredActor, EVRHandType Hand)
{
	// nullsub
}

void ASWGVRCharacter::OnHeldActorDestroyed(AActor* DestroyedActor)
{
	RemoveDestroyedActor(LeftController, DestroyedActor);
	RemoveDestroyedActor(RightController, DestroyedActor);
	TrackedActors.Remove(DestroyedActor);
}

void ASWGVRCharacter::OnGrabHoverEnd_Implementation(AActor* Grabbable, EVRHandType Hand)
{
	// nullsub
}

void ASWGVRCharacter::OnGrabHoverBegin_Implementation(AActor* Grabbable, EVRHandType Hand)
{
	// nullsub
}

void ASWGVRCharacter::OnGrab_Implementation(AActor* Grabbable, EVRHandType Hand)
{
	// nullsub
}

bool ASWGVRCharacter::IsUsingPad() const
{
	return bIsUsingPadForHand;
}

bool ASWGVRCharacter::IsInVRMode() const
{
	return USWGVRUtil::CurrentPlayType == EVRPlayType::UsingVR;
}

bool ASWGVRCharacter::InitialIsInVR() const
{
	if (GEngine && GEngine->XRSystem)
	{
		// todo dont call GetHMDDevice twice
		bool bIsHMDConnected = GEngine->XRSystem->GetHMDDevice()->IsHMDConnected();
		GEngine->XRSystem->GetHMDDevice()->EnableHMD(bIsHMDConnected);

		auto stereoRenderingDevice = GEngine->XRSystem->GetStereoRenderingDevice();
		if (stereoRenderingDevice)
		{
			stereoRenderingDevice->EnableStereo(bIsHMDConnected);
		}

		// unused
		FName VRSystemName = GEngine->XRSystem->GetSystemName();

		USWGVRUtil::ChangePlayType(bIsHMDConnected ? EVRPlayType::UsingVR : EVRPlayType::NotUsingVR);
		return true;
	}
	else
	{
		USWGVRUtil::ChangePlayType(EVRPlayType::NotUsingVR);
		return false;
	}
}

void ASWGVRCharacter::GrabGrabbable(AActor* Grabbable, EVRHandType Hand, bool bForce)
{
	if (Grabbable)
	{
		if (Hand == EVRHandType::Left)
		{
			AttemptGrab(Hand, &LeftController, Grabbable, EVRHandType::Left,
			            LeftAttachPoint, &LeftController);
		}
		else if (Hand == EVRHandType::Right)
		{
			AttemptGrab(Hand, &RightController, Grabbable, EVRHandType::Right,
			            RightAttachPoint, &RightController);
		}
	}
}

FName ASWGVRCharacter::GetPadTrackingSource() const
{
	return "Pad";
}

FMotionControllerInfo& ASWGVRCharacter::GetHandInfo(EVRHandType Hand)
{
	static FMotionControllerInfo EmptyControllerInfo;

	if (Hand == EVRHandType::Left)
	{
		return LeftController;
	}
	if (Hand == EVRHandType::Right)
	{
		return RightController;
	}

	return EmptyControllerInfo;
}

FHeldGrabbableInfo& ASWGVRCharacter::GetGrabbableInfo(const AActor* HeldActor)
{
	static FHeldGrabbableInfo EmptyHeldInfo;
	FHeldGrabbableInfo* GrabbableInfo = LeftController.HeldInfo.Find(HeldActor);
	return GrabbableInfo ? *GrabbableInfo : EmptyHeldInfo;
}

FVector ASWGVRCharacter::GetHeldOffset(EVRHandType Hand, int32 ItemIndex)
{
	FMotionControllerInfo& HandInfo = GetHandInfo(Hand);
	if (ItemIndex >= 0 && ItemIndex < HandInfo.HeldGrabbables.Num())
	{
		FHeldGrabbableInfo& GrabbableInfo = HandInfo.HeldInfo[HandInfo.HeldGrabbables[ItemIndex]];
		return GrabbableInfo.AttachmentRelativeLocation;
	}
	return FVector::ZeroVector;
}


USceneComponent* ASWGVRCharacter::GetHandAttachPoint(EVRHandType Hand) const
{
	if (Hand != EVRHandType::None)
	{
		if (Hand == EVRHandType::Left)
		{
			return LeftAttachPoint;
		}
		if (Hand == EVRHandType::Right)
		{
			return RightAttachPoint;
		}
	}
	return nullptr;
}

ESWGVRControllerType ASWGVRCharacter::GetControllerDeviceType() const
{
	if (InitialIsInVR())
	{
		FName VRSystemName = GEngine->XRSystem->GetSystemName();
		return VRSystemName == "OculusHMD"
			       ? ESWGVRControllerType::Oculus
			       : ESWGVRControllerType::SteamVR;
	}
	else
	{
		return ASWGVRPlayerControllerBase::GetStaticIsUsingGamepad()
			       ? ESWGVRControllerType::XBox // lol
			       : ESWGVRControllerType::MouseAndKeyboard;
	}
}

void ASWGVRCharacter::AddHeldOffset(EVRHandType Hand, const FVector& AdditiveValue, int32 ItemIndex)
{
	FMotionControllerInfo& HandInfo = GetHandInfo(Hand);
	if (ItemIndex >= 0 && ItemIndex < HandInfo.HeldGrabbables.Num())
	{
		FHeldGrabbableInfo& GrabbableInfo = HandInfo.HeldInfo[HandInfo.HeldGrabbables[ItemIndex]];
		GrabbableInfo.AttachmentRelativeLocation += AdditiveValue;
	}
}

void ASWGVRCharacter::AttemptGrab(EVRHandType Hand, FMotionControllerInfo* OtherControllerInfo, AActor* hoverActor,
                                  EVRHandType OtherHand, USceneComponent* AttachmentComp,
                                  FMotionControllerInfo* ControllerInfo)
{
	// TODO
}

#undef NEW_INFINITY