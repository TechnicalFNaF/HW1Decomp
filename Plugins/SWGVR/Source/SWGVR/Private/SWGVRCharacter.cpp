#include "SWGVRCharacter.h"

#include "DrawDebugHelpers.h"
#include "IHeadMountedDisplay.h"
#include "IXRTrackingSystem.h"
#include "FileHelper.h"

#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "MotionControllerComponent.h"
#include "SWGGrabbable.h"
#include "SWGVRCameraLocator.h"
#include "SWGVRHoverReceiver.h"
#include "SWGVRInteractive.h"
#include "SWGVRPlayerControllerBase.h"
#include "SWGVRSettings.h"
#include "SWGVRUtil.h"
#include "Engine/Engine.h"

#include "GameFramework/WorldSettings.h"
#include "Kismet/GameplayStatics.h"

#undef INFINITY
#define INFINITY ((float)(_HUGE_ENUF * _HUGE_ENUF))

ASWGVRCharacter::ASWGVRCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	LeftGrabActionName = "LeftGrab";
	RightGrabActionName = "RightGrab";

	ThrowMagnitude = 1.f;
	bGrabClosest = true;
	HandsThatGrab = EVRHandType::Both;
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

	FPSMin = INFINITY;
	FPSMax = -INFINITY;

	FPSAverageOverTime = 0.f;
	PerfCounterSeconds = 0.f;
	TotalPerfSeconds = 0.f;

	VRModeEnabled = true;
	WasPreviouslyInVR = true;

	LeftController.ClosestGrabbableActor = nullptr;
	LeftController.ClosestGrabbableDistance = INFINITY;
	LeftController.ClosestHoveredActor = nullptr;
	LeftController.ClosestHoveredComponent = nullptr;
	LeftController.ClosestDistance = INFINITY;
	LeftController.bIsTracked = false;

	RightController.ClosestGrabbableActor = nullptr;
	RightController.ClosestGrabbableDistance = INFINITY;
	RightController.ClosestHoveredActor = nullptr;
	RightController.ClosestHoveredComponent = nullptr;
	RightController.ClosestDistance = INFINITY;
	RightController.bIsTracked = false;

	bIsUsingPadForHand = false;
	m_previousWorldToMeters = 100.f;

	NonVROffset = FVector::ZeroVector;
	bUseNonVROffset = false;

	VROriginComp = CreateDefaultSubobject<USceneComponent>("VRCameraOrigin");
	VROriginComp->SetupAttachment(GetRootComponent());

	VRCameraAdjuster = CreateDefaultSubobject<USceneComponent>("VRCameraAdjuster");
	VRCameraAdjuster->SetupAttachment(VROriginComp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(VRCameraAdjuster);

	LeftHandComponent = CreateDefaultSubobject<UMotionControllerComponent>("LeftHand");
	LeftHandComponent->SetupAttachment(VRCameraAdjuster);
	LeftHandComponent->SetTrackingSource(EControllerHand::Left);

	LeftHandTrigger = CreateDefaultSubobject<USphereComponent>("LeftHandTrigger");
	LeftHandTrigger->SetupAttachment(LeftHandComponent);

	LeftAttachPoint = CreateDefaultSubobject<USceneComponent>("LeftAttachPoint");
	LeftAttachPoint->SetupAttachment(LeftHandComponent);

	RightHandComponent = CreateDefaultSubobject<UMotionControllerComponent>("RightHand");
	RightHandComponent->SetupAttachment(VRCameraAdjuster);
	RightHandComponent->SetTrackingSource(EControllerHand::Right);

	RightHandTrigger = CreateDefaultSubobject<USphereComponent>("RightHandTrigger");
	RightHandTrigger->SetupAttachment(RightHandComponent);

	RightAttachPoint = CreateDefaultSubobject<USceneComponent>("RightAttachPoint");
	RightAttachPoint->SetupAttachment(RightHandComponent);

	PadMotionComponent = CreateDefaultSubobject<UMotionControllerComponent>("PadMotion");
	PadMotionComponent->SetupAttachment(VRCameraAdjuster);

	PadTrigger = CreateDefaultSubobject<USphereComponent>("PadTrigger");
	PadTrigger->SetupAttachment(PadMotionComponent);

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
	if (bool Contained = ControllerInfo.HeldGrabbables.Contains(DestroyedActor))
	{
		ControllerInfo.HeldGrabbables.Remove(DestroyedActor);
		ReleaseGrabbable(DestroyedActor, Contained, false, FVector::ZeroVector);
	}

	ControllerInfo.HeldGrabbables.Remove(DestroyedActor);
	ControllerInfo.HeldInfo.Remove(DestroyedActor);
	ControllerInfo.HoveredGrabbables.Remove(DestroyedActor);
	ControllerInfo.HoveredObjects.Remove(DestroyedActor);

	if (ControllerInfo.ClosestHoveredActor == DestroyedActor)
	{
		ControllerInfo.ClosestDistance = INFINITY;
		ControllerInfo.ClosestHoveredActor = nullptr;
	}
}

void ASWGVRCharacter::SendOnHoverBeginEvents(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             EVRHandType Hand, FMotionControllerInfo& ControllerInfo)
{
	if (IsInVRMode())
	{
		if (!ControllerInfo.HeldGrabbables.Contains(OtherActor))
		{
			if (OtherActor->Implements<USWGVRHoverReceiver>())
			{
				ControllerInfo.HoveredObjects.Add(OtherActor);
				if (!TrackedActors.Contains(OtherActor))
				{
					OtherActor->OnDestroyed.AddDynamic(this, &ASWGVRCharacter::OnHeldActorDestroyed);
					TrackedActors.Add(OtherActor);
				}
			}

			if (OtherActor->Implements<USWGGrabbable>())
			{
				ControllerInfo.HeldGrabbables.Add(OtherActor);
				if (!TrackedActors.Contains(OtherActor))
				{
					OtherActor->OnDestroyed.AddDynamic(this, &ASWGVRCharacter::OnHeldActorDestroyed);
					TrackedActors.Add(OtherActor);
				}
			}
		}
	}
}

void ASWGVRCharacter::SendOnHoverEndEvents(AActor* OtherActor, EVRHandType Hand, FMotionControllerInfo& ControllerInfo)
{
	if (IsInVRMode())
	{
		if (OtherActor->Implements<USWGVRHoverReceiver>())
		{
			if (OtherActor == ControllerInfo.ClosestHoveredActor)
			{
				ISWGVRHoverReceiver::Execute_OnVRHoverEnd(OtherActor, this, Hand);
				OnHoverEnd(OtherActor, Hand);
				ControllerInfo.ClosestDistance = INFINITY;
			}
			ControllerInfo.HoveredObjects.Remove(OtherActor);
		}

		if (OtherActor->Implements<USWGGrabbable>())
		{
			ControllerInfo.HoveredGrabbables.Remove(OtherActor);
		}
	}
}

// TBaseFunctorDelegateInstance_TTypeWrapper_void____cdecl_void___lambda_967afc17173eb4af74b07a8953f78ecc___::Execute
void ASWGVRCharacter::OnGrabAction(EVRHandType Hand)
{
	FMotionControllerInfo ControllerInfo = GetHandInfo(Hand);

	EVRHandType OtherHand = (Hand == EVRHandType::Left ? EVRHandType::Right : EVRHandType::Left);
	FMotionControllerInfo OtherControllerInfo = GetHandInfo(OtherHand);

	USceneComponent* AttachPoint = (Hand == EVRHandType::Left ? LeftAttachPoint : RightAttachPoint);

	if (!IsInVRMode() && ControllerInfo.HeldGrabbables.Num() > 0)
	{
		ReleaseAll(Hand, true, false, FVector::ZeroVector);
	}
	else if (bHoldMultiple || ControllerInfo.HeldGrabbables.Num() <= 0)
	{
		if (bGrabClosest)
		{
			if (ControllerInfo.ClosestGrabbableActor)
			{
				AttemptGrab(Hand, &OtherControllerInfo, ControllerInfo.ClosestGrabbableActor, OtherHand, AttachPoint, &ControllerInfo);
			}
		}
		else
		{
			for (int i = 0; i != ControllerInfo.HoveredGrabbables.Num(); i++)
			{
				AActor* HoveredActor = ControllerInfo.HoveredGrabbables[i];
				if (HoveredActor)
				{
					AttemptGrab(Hand, &OtherControllerInfo, HoveredActor, OtherHand, AttachPoint, &ControllerInfo);
				}
			}
		}
	}
}

// TBaseFunctorDelegateInstance_TTypeWrapper_void____cdecl_void___lambda_3ae24b327b54816782408ba530af2541___::Execute
void ASWGVRCharacter::OnReleaseAction(EVRHandType Hand)
{
	FMotionControllerInfo ControllerInfo = GetHandInfo(Hand);

	if (IsInVRMode())
	{
		FVector ThrowVelocity = ThrowMagnitude * ControllerInfo.Velocity;
		for (int i = 0; i != ControllerInfo.HeldGrabbables.Num(); i++)
		{
			AActor* HeldGrabbable = ControllerInfo.HeldGrabbables[i];
			if (HeldGrabbable)
			{
				ReleaseGrabbableInternal(HeldGrabbable, Hand, false, ThrowVelocity, &ControllerInfo);
			}
		}
	}
}

void ASWGVRCharacter::BindGrabActions(class UInputComponent* PlayerInputComponent, EVRHandType Hand, FName ActionName)
{
	if (static_cast<bool>(HandsThatGrab & Hand) && ActionName.IsValid())
	{
		FInputActionBinding GrabPressedBinding = FInputActionBinding(ActionName, IE_Pressed);
		FInputActionHandlerSignature& PressedDelegate = GrabPressedBinding.ActionDelegate.GetDelegateForManualSet();

		PressedDelegate.BindLambda([this, Hand]()
		{
				OnGrabAction(Hand);
		});
		PlayerInputComponent->AddActionBinding(GrabPressedBinding);
		
		FInputActionBinding GrabReleasedBinding = FInputActionBinding(ActionName, IE_Released);
		FInputActionHandlerSignature& ReleasedDelegate = GrabReleasedBinding.ActionDelegate.GetDelegateForManualSet();

		ReleasedDelegate.BindLambda([this, Hand]()
		{
				OnReleaseAction(Hand);
		});
		PlayerInputComponent->AddActionBinding(GrabReleasedBinding);
	}
}

bool ASWGVRCharacter::ReleaseGrabbableInternal(AActor* Grabbable, EVRHandType Hand, bool bForce,
	const FVector& Velocity, FMotionControllerInfo* ControllerInfo)
{
	if (!IsValid(Grabbable) || !bForce && !ISWGGrabbable::Execute_AttemptRelease(Grabbable, this, Hand))
	{
		return false;
	}

	ControllerInfo->HeldGrabbables.Remove(Grabbable);
	
	FVector thrownVelocity = Velocity;
	if (IsValid(Grabbable))
	{
		FHeldGrabbableInfo* GrabbableInfo = ControllerInfo->HeldInfo.Find(Grabbable);
		if (GrabbableInfo)
		{
			if (GrabbableInfo->GrabSnapType == EGrabSnapType::SnapToHand)
			{
				Grabbable->DetachFromActor({ EDetachmentRule::KeepWorld, true });
			}

			UPrimitiveComponent* GrabbableRoot = Cast<UPrimitiveComponent>(Grabbable->GetRootComponent());
			if (GrabbableRoot)
			{
				GrabbableRoot->SetCollisionEnabled(GrabbableInfo->Collision);
				GrabbableRoot->SetSimulatePhysics(GrabbableInfo->bUsePhysics);
				if (GrabbableRoot->IsSimulatingPhysics())
				{
					GrabbableRoot->AddImpulse(thrownVelocity, NAME_None, true);
				}
			}
			
			ControllerInfo->HeldInfo.Remove(Grabbable);
			goto LABEL_32; // todo maybe not use goto lol
		}
	}
	return false;

LABEL_32:
	ISWGGrabbable::Execute_OnVRReleased(Grabbable, this, Hand, thrownVelocity);
	OnRelease(Grabbable, Hand);
	OnActorReleased.Broadcast(this, Grabbable, Hand);

	USphereComponent* HandTrigger = nullptr;
	if (Hand == EVRHandType::Left)
	{
		HandTrigger = LeftHandTrigger;
	}
	else if (Hand == EVRHandType::Right)
	{
		HandTrigger = RightHandTrigger;
	}

	if (IsInVRMode() && IsValid(Grabbable) &&
		HandTrigger && HandTrigger->IsOverlappingActor(Grabbable))
	{
		if (Grabbable->Implements<USWGVRHoverReceiver>())
		{
			if (!ControllerInfo->HoveredObjects.Contains(Grabbable))
			{
				ISWGVRHoverReceiver::Execute_OnVRHoverBegin(Grabbable, this, Hand);
				ControllerInfo->HoveredObjects.AddUnique(Grabbable);
				OnHoverBegin(Grabbable, Hand);
			}
		}
		ControllerInfo->ClosestHoveredActor = Grabbable;
		ControllerInfo->HoveredGrabbables.AddUnique(Grabbable);
	}
	
	return true;
}

// TBaseFunctorDelegateInstance_TTypeWrapper_void____cdecl_void___lambda_3a9174d4fada2ec770f5cf32c01cad19___::Execute
void ASWGVRCharacter::OnInteractAction(EVRHandType Hand)
{
	FMotionControllerInfo ControllerInfo = GetHandInfo(Hand);
	
	for (int i = 0; i != ControllerInfo.HoveredObjects.Num(); i++)
	{
		SendOnVRInteract(ControllerInfo.HoveredObjects[i], Hand);
	}

	for (int i = 0; i != ControllerInfo.HoveredGrabbables.Num(); i++)
	{
		SendOnVRInteract(ControllerInfo.HoveredGrabbables[i], Hand);
	}
}

void ASWGVRCharacter::SendOnVRInteract(UObject* Object, EVRHandType Hand)
{
	if (IsValid(Object) && Object->Implements<USWGVRInteractive>())
	{
		ISWGVRInteractive::Execute_OnVRInteract(Object, this, Hand);
	}
}

void ASWGVRCharacter::BindInteractionActions(UInputComponent* PlayerInputComponent, EVRHandType Hand, FName ActionName)
{
	if (static_cast<bool>(Hand & HandsThatInteract))
	{
		FInputActionBinding InteractionBinding = FInputActionBinding(ActionName, IE_Pressed);
		FInputActionHandlerSignature& PressedDelegate = InteractionBinding.ActionDelegate.GetDelegateForManualSet();

		PressedDelegate.BindLambda([this, Hand]()
		{
				OnInteractAction(Hand);
		});
		PlayerInputComponent->AddActionBinding(InteractionBinding);
	}
}

void ASWGVRCharacter::ChangeHoveredActor(AActor*& CurrentHoveredActor, UPrimitiveComponent*& CurrentHoveredComponent,
										 AActor* newHoverActor, UPrimitiveComponent* newHoverComponent,
										 EVRHandType Hand)
{
	if (CurrentHoveredComponent != newHoverComponent)
	{
		if (IsValid(CurrentHoveredActor) &&
			CurrentHoveredActor->Implements<USWGVRHoverReceiver>() &&
			CurrentHoveredActor->Implements<USWGVRHoverReceiver>()) // not sure why they check this twice
		{
			ISWGVRHoverReceiver::Execute_OnVRHoverComponentEnd(
				CurrentHoveredActor, this, CurrentHoveredComponent, Hand);
		}
		if (IsValid(newHoverActor) && newHoverActor->Implements<USWGVRHoverReceiver>())
		{
			// dont know why they're checking this is != again
			if (newHoverComponent != CurrentHoveredComponent && CurrentHoveredComponent)
				ISWGVRHoverReceiver::Execute_OnVRHoverComponentBegin(
				  newHoverActor, this, newHoverComponent, Hand);
		}
		CurrentHoveredComponent = newHoverComponent;
	}

	if (CurrentHoveredActor != newHoverActor)
	{
		if (IsValid(CurrentHoveredActor) && CurrentHoveredActor->Implements<USWGVRHoverReceiver>())
		{
			ISWGVRHoverReceiver::Execute_OnVRHoverEnd(CurrentHoveredActor, this, Hand);
			OnHoverEnd(CurrentHoveredActor, Hand);
			
			TArray<AActor*>& HoveredGrabbables = Hand == EVRHandType::Left ? LeftController.HoveredGrabbables : RightController.HoveredGrabbables;
			HoveredGrabbables.Remove(CurrentHoveredActor);
		}
		CurrentHoveredActor = newHoverActor;

		if (IsValid(newHoverActor) && newHoverActor->Implements<USWGVRHoverReceiver>())
		{
			ISWGVRHoverReceiver::Execute_OnVRHoverBegin(newHoverActor, this, Hand);
			OnHoverBegin(newHoverActor, Hand);
			TArray<AActor*>& HoveredGrabbables = Hand == EVRHandType::Left ? LeftController.HoveredGrabbables : RightController.HoveredGrabbables;
			HoveredGrabbables.Add(newHoverActor);
		}
	}
}

void ASWGVRCharacter::ProcMotionController(EVRHandType Hand, USceneComponent* MotionController,
                                           FMotionControllerInfo& ControllerInfo, USceneComponent* AttachPoint)
{
	if (IsInVRMode())
	{
		UMotionControllerComponent* ProcMotionComp = Cast<UMotionControllerComponent>(MotionController);
		if (ProcMotionComp)
		{
			if (ControllerInfo.bIsTracked)
			{
				AActor* ClosestHoveredActor = ControllerInfo.ClosestHoveredActor;
				ControllerInfo.bIsTracked = false;
				ControllerInfo.ClosestDistance = INFINITY;
				if (IsValid(ClosestHoveredActor))
				{
					if (ClosestHoveredActor->Implements<USWGVRHoverReceiver>())
					{
						ISWGVRHoverReceiver::Execute_OnVRHoverEnd(ControllerInfo.ClosestHoveredActor, this, Hand);
						OnHoverEnd(ControllerInfo.ClosestHoveredActor, Hand);
					}
					ControllerInfo.ClosestHoveredActor = nullptr;
				}
				
				ControllerInfo.HoveredGrabbables.Empty();
				ControllerInfo.HoveredObjects.Empty();
				ControllerInfo.OldWorldPosition = FVector::ZeroVector;
				ControllerInfo.Velocity = FVector::ZeroVector;
			}
		}
		else if (!ControllerInfo.bIsTracked)
		{
			ControllerInfo.bIsTracked = true;

			ControllerInfo.OldWorldPosition = MotionController->GetComponentLocation();
		}
	}
	
	bool v22 = ControllerInfo.PreviousPositions.Num() <= 9;
	FVector CompLocation = MotionController->GetComponentLocation();

	ControllerInfo.InstantaneousVelocity = CompLocation - ControllerInfo.OldWorldPosition;
	while (ControllerInfo.PreviousPositions.Num() > 9)
	{
		ControllerInfo.PreviousPositions.RemoveAt(0);
	}

	ControllerInfo.PreviousPositions.Add(CompLocation);

	USphereComponent* TriggerToUse = nullptr;
	if (Hand == EVRHandType::Left)
	{
		TriggerToUse = LeftHandTrigger;
	}

	if (Hand == EVRHandType::Right)
	{
		TriggerToUse = RightHandTrigger;
	}

	if (IsInVRMode() && TriggerToUse && ControllerInfo.HoveredObjects.Num() > 0)
	{
		for (int i = 0; i != ControllerInfo.HoveredObjects.Num(); i++)
		{
			AActor* HoveredActor = ControllerInfo.HoveredObjects[i];
			if (IsValid(HoveredActor))
			{
				if (!TriggerToUse->IsOverlappingActor(HoveredActor))
				{
					SendOnHoverEndEvents(HoveredActor, Hand, ControllerInfo);
				}
			}
		}
	}

	// TODO 140303DB4

	bool v64 = false;
	if (!bIsUsingPadForHand && USWGVRUtil::CurrentPlayType != EVRPlayType::NotUsingVR)
	{
		v64 = false;
	}

	FCollisionQueryParams CollisionQuery{};
	CollisionQuery.AddIgnoredActors(ControllerInfo.HeldGrabbables);
	CollisionQuery.TraceTag = "ForceGrabTrace";
	CollisionQuery.bFindInitialOverlaps = true;
	CollisionQuery.MobilityType = EQueryMobilityType::Any;
	CollisionQuery.bIgnoreTouches = true;
	CollisionQuery.IgnoreMask = 0;

	FVector EndPos = PadLineTraceDistance * MotionController->GetComponentTransform().TransformVectorNoScale(FVector(1.f, 0.f, 0.f));
	EndPos += CompLocation;

	bool bHoverActor = false;
	bool bGrabbbable = false;

	FHitResult OutHit;
	if (GetWorld()->LineTraceSingleByChannel(OutHit, CompLocation, EndPos, ECC_Visibility, CollisionQuery))
	{
		if (OutHit.Actor.IsValid())
		{
			if (OutHit.Actor->Implements<USWGVRHoverReceiver>())
			{
				bHoverActor = true;
			}

			if (OutHit.Actor->Implements<USWGGrabbable>())
			{
				bGrabbbable = true;
				ControllerInfo.ClosestGrabbableDistance = OutHit.Distance;
			}
			else
			{
				ControllerInfo.ClosestGrabbableDistance = INFINITY;
				bGrabbbable = false;
			}
			ControllerInfo.ClosestGrabbableActor = OutHit.Actor.Get();

			if (!IsInVRMode())
			{
				ChangeHoveredActor(ControllerInfo.ClosestHoveredActor, ControllerInfo.ClosestHoveredComponent, OutHit.Actor.Get(), OutHit.Component.Get(), Hand);
			}
		}
	}
	else if (!IsInVRMode())
	{
		ControllerInfo.ClosestGrabbableActor = nullptr;
		ControllerInfo.ClosestGrabbableDistance = INFINITY;
		ChangeHoveredActor(ControllerInfo.ClosestHoveredActor, ControllerInfo.ClosestHoveredComponent, nullptr, nullptr, Hand);
	}

	// TODO: 140304075
	if (IsInVRMode())
	{
		// DO VR MODE STUFF - 14030407A
	}

	for (auto HeldInfo : GetHandInfo(Hand).HeldInfo)
	{
		if (IsValid(HeldInfo.Key))
		{
			const USWGVRSettings* SWGVRSettings = GetDefault<USWGVRSettings>();
			if (true /* BYTE4(v98->PrimaryActorTick.Target) */)
			{
				ProcessInterpolatedGrab(AttachPoint->GetComponentTransform(), HeldInfo.Value, HeldInfo.Key, Hand);
			}
			else
			{
				FTransform AttachmentTransform = AttachPoint->GetComponentTransform();

				FVector Loc = AttachmentTransform.TransformPosition(HeldInfo.Value.AttachmentRelativeLocation);
				FQuat Rot = AttachmentTransform.TransformRotation(HeldInfo.Value.AttachmentRelativeRotation.Quaternion());

				HeldInfo.Key->SetActorLocationAndRotation(Loc, Rot);
			}
		}
	}
}

void ASWGVRCharacter::FindClosestActor(FVector CurrentLocation, float& closestDist, AActor*& closestActor,
                                       TArray<AActor*>& actorList)
{
	closestActor = nullptr;
	closestDist = INFINITY;
	
	for (auto Actor : actorList)
	{
		if (IsValid(Actor))
		{
			float Dist = FVector::DistSquared(CurrentLocation, Actor->GetActorLocation());
			if (Dist < closestDist)
			{
				closestDist = Dist;
				closestActor = Actor;
			}
		}
	}
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

			result = result.Append(PerfString);
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
	FMotionControllerInfo& HandInfo = GetHandInfo(Hand);
	if (ItemIndex >= 0 && ItemIndex < HandInfo.HeldGrabbables.Num())
	{
		FHeldGrabbableInfo& GrabbableInfo = HandInfo.HeldInfo[HandInfo.HeldGrabbables[ItemIndex]];
		GrabbableInfo.AttachmentRelativeLocation = NewOffset;
	}
}

void ASWGVRCharacter::SetCameraWorldRotation(const FRotator& Rotation)
{
	VRCameraAdjuster->SetWorldRotation(Rotation);
}

void ASWGVRCharacter::SetCameraWorldLocationAndRotation(const FVector& Location, const FRotator& Rotation)
{
	VRCameraAdjuster->SetWorldLocationAndRotation(Location, Rotation);
	NonVROffset = VRCameraAdjuster->RelativeLocation;
	EyeOffset = NonVROffset.Y;
}

void ASWGVRCharacter::SetCameraWorldLocation(const FVector& Location)
{
	VRCameraAdjuster->SetWorldLocation(Location);
	NonVROffset = Location;
	EyeOffset = NonVROffset.Y;
	bUseNonVROffset = true;
}

void ASWGVRCharacter::SetCameraRelativeRotation(const FRotator& Rotation)
{
	VRCameraAdjuster->SetRelativeRotation(Rotation);
}

void ASWGVRCharacter::SetCameraRelativeLocationAndRotation(const FVector& Location, const FRotator& Rotation)
{
	VRCameraAdjuster->SetRelativeLocationAndRotation(Location, Rotation);
	NonVROffset = Location;
	EyeOffset = Location.Y;
	bUseNonVROffset = true;
}

void ASWGVRCharacter::SetCameraRelativeLocation(const FVector& Location)
{
	VRCameraAdjuster->SetRelativeLocation(Location);
	NonVROffset = Location;
	EyeOffset = Location.Y;
}

void ASWGVRCharacter::ReleaseGrabbable(AActor* Grabbable, bool bForce, bool bOverrideVelocity, FVector Velocity)
{
	if (LeftController.HeldGrabbables.Contains(Grabbable))
	{
		FVector NewVelocity = bOverrideVelocity
			? Velocity
			: ThrowMagnitude * RightController.Velocity;
		ReleaseGrabbableInternal(Grabbable, EVRHandType::Left, bForce, NewVelocity, &LeftController);
	}
	if (RightController.HeldGrabbables.Contains(Grabbable))
	{
		FVector NewVelocity = bOverrideVelocity
			? Velocity
			: ThrowMagnitude * RightController.Velocity;
		ReleaseGrabbableInternal(Grabbable, EVRHandType::Right, bForce, NewVelocity, &RightController);
	}
}

void ASWGVRCharacter::ReleaseAll(EVRHandType Hand, bool bForce, bool bOverrideVelocity, FVector Velocity)
{
	if (static_cast<bool>(Hand & EVRHandType::Right))
	{
		// todo maybe not copy here
		TArray<AActor*> grabbableList = RightController.HeldGrabbables;
		for (AActor* Grabbable : grabbableList)
		{
			ReleaseGrabbable(Grabbable, bForce, bOverrideVelocity, Velocity);
		}
	}
	
	if (static_cast<bool>(Hand & EVRHandType::Left))
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
	bool canGrab = false;
	EGrabSnapType SnapType = EGrabSnapType::None;
	bool snapLocation = false;
	bool snapRotation = false;

	FVector AttachmentOffsetLocation;
	FRotator AttachmentOffsetRotation;

	FHeldGrabbableInfo GrabbableInfo;

	if (IsValid(hoverActor))
	{
		if (hoverActor->Implements<USWGGrabbable>())
		{
			//	EVRHandType Hand, bool& canGrab, EGrabSnapType& SnapType, bool& snapLocation, bool& snapRotation, FVector& AttachmentOffsetLocation, FRotator& AttachmentOffsetRotation
			ISWGGrabbable::Execute_AttemptGrab(hoverActor, this, Hand, canGrab, SnapType, snapLocation, snapRotation, AttachmentOffsetLocation, AttachmentOffsetRotation);
		}

		if (canGrab)
		{
			if (OtherControllerInfo->HeldGrabbables.Contains(hoverActor) || ReleaseGrabbableInternal(hoverActor, OtherHand, false, FVector::ZeroVector, OtherControllerInfo))
			{
				if (!bHoldMultiple)
				{
					ReleaseAll(Hand, true, false, FVector::ZeroVector);
				}

				if (hoverActor->Implements<USWGVRHoverReceiver>())
				{
					ISWGVRHoverReceiver::Execute_OnVRHoverEnd(hoverActor, this, Hand);
					OnHoverEnd(hoverActor, Hand);
				}

				if (!hoverActor)
				{
					OnGrab(hoverActor, Hand);
					OnActorGrabbed.Broadcast(this, hoverActor, Hand);
					ISWGGrabbable::Execute_OnVRGrabbed(hoverActor, this, Hand);
				}

				if (!hoverActor)
				{
					OnGrab(hoverActor, Hand);
					OnActorGrabbed.Broadcast(this, hoverActor, Hand);
					ISWGGrabbable::Execute_OnVRGrabbed(hoverActor, this, Hand);;
				}

				FRotator HoverActorRot = hoverActor->GetActorRotation();
				if (SnapType != EGrabSnapType::SnapToHand)
					goto LABEL_55;

				if (SnapType == EGrabSnapType::SnapToHand)
				{
					EAttachmentRule Rule = (EAttachmentRule)((SnapType != EGrabSnapType::LocationToHand) + 1);
					hoverActor->AttachToComponent(AttachmentComp, FAttachmentTransformRules(Rule, Rule, EAttachmentRule::KeepWorld, false));
					// TODO: Verify

					if (snapLocation)
					{
						hoverActor->AddActorLocalOffset(AttachmentOffsetLocation);
					}

					if (snapRotation)
					{
						hoverActor->AddActorLocalRotation(AttachmentOffsetRotation);
					}
				}
				else
				{
					if (bIsUsingPadForHand || USWGVRUtil::GetPlayType() == EVRPlayType::UsingVR)
					{
						GrabbableInfo.AttachmentRelativeLocation = AttachmentOffsetLocation;
						GrabbableInfo.AttachmentRelativeRotation = AttachmentOffsetRotation;
						GrabbableInfo.IsLerpingToHand = true;
					}
					else
					{
						GrabbableInfo.IsLerpingToHand = false;

						LABEL_55:

						FVector HoverLocation = hoverActor->GetActorLocation();
						FVector InversedLocation = AttachmentComp->GetComponentTransform().InverseTransformPosition(HoverLocation);

						GrabbableInfo.AttachmentRelativeLocation = HoverLocation;

						FRotator HoverRotation = hoverActor->GetActorRotation();
						FQuat InversedRotation = AttachmentComp->GetComponentTransform().InverseTransformRotation(HoverRotation.Quaternion());

						GrabbableInfo.AttachmentRelativeRotation = HoverRotation;

						if (UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(hoverActor->GetRootComponent()))
						{
							GrabbableInfo.Collision = PrimitiveComp->GetCollisionEnabled();
							GrabbableInfo.bUsePhysics = PrimitiveComp->IsSimulatingPhysics();

							PrimitiveComp->SetSimulatePhysics(false);
							PrimitiveComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
						}
						GrabbableInfo.GrabSnapType = SnapType;

						ControllerInfo->HoveredGrabbables.Remove(hoverActor);
						ControllerInfo->HeldGrabbables.Add(hoverActor);

						if (!TrackedActors.Contains(hoverActor))
						{
							TrackedActors.Add(hoverActor);
							hoverActor->OnDestroyed.AddDynamic(this, &ASWGVRCharacter::OnHeldActorDestroyed);
						}
						GrabbableInfo.PrimitiveCollisionInfo.Empty(); // Maybe wrong?

						ControllerInfo->HeldInfo.Add(hoverActor, GrabbableInfo);

						OnGrab(hoverActor, Hand);
						OnActorGrabbed.Broadcast(this, hoverActor, Hand);
						ISWGGrabbable::Execute_OnVRGrabbed(hoverActor, this, Hand);
					}
				}
			}
		}
	}
}