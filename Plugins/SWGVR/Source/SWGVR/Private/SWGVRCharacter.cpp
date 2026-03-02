#include "SWGVRCharacter.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "MotionControllerComponent.h"

ASWGVRCharacter::ASWGVRCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	this->CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	this->VROriginComp = CreateDefaultSubobject<USceneComponent>(TEXT("VRCameraOrigin"));
	this->VRCameraAdjuster = CreateDefaultSubobject<USceneComponent>(TEXT("VRCameraAdjuster"));
	this->bPositionalHeadTracking = false;
	this->LeftHandComponent = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftHand"));
	this->RightHandComponent = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightHand"));
	this->PadMotionComponent = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("PadMotion"));
	this->LeftHandTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHandTrigger"));
	this->RightHandTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("RightHandTrigger"));
	this->PadTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("PadTrigger"));
	this->LeftAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LeftAttachPoint"));
	this->RightAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RightAttachPoint"));
	this->PadAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("PadAttachPoint"));
	this->PadInteractionPointer = CreateDefaultSubobject<UArrowComponent>(TEXT("PadInteractionPointer"));
	this->HandsThatGrab = EVRHandType::Both;
	this->LeftGrabActionName = TEXT("LeftGrab");
	this->RightGrabActionName = TEXT("RightGrab");
	this->ThrowMagnitude = 1.00f;
	this->bGrabClosest = true;
	this->bHoldMultiple = false;
	this->HandsThatInteract = EVRHandType::Both;
	this->LeftInteractActionName = TEXT("LeftInteract");
	this->RightInteractActionName = TEXT("RightInteract");
	this->VRTrackingOrigin = EHMDTrackingOrigin::Floor;
	this->bUseEyeOffsetForEyeTracking = true;
	this->EyeOffset = 100.00f;
	this->bUseHandForPad = false;
	this->HandToUseAsPad = EVRHandType::Right;
	this->PadLineTraceDistance = 100.00f;
	this->LerpGrabSpeed = 1000.00f;
	this->bPerfCounterEnabled = false;
	//this->FPSMin = INFINITY;
	//this->FPSMax = -INFINITY;
	this->FPSAverageOverTime = 0.00f;
	this->FPSImmediate = 0.00f;
	this->PerfCounterSeconds = 0.00f;
	this->PerfCounterImmediateSeconds = 0.00f;
	this->TotalPerfSeconds = 0.00f;
	this->FrameCounterForAverage = 0;
	this->VRModeEnabled = true;
	this->CameraComp->SetupAttachment(VRCameraAdjuster);
	this->VROriginComp->SetupAttachment(RootComponent);
	this->VRCameraAdjuster->SetupAttachment(VROriginComp);
	this->LeftHandComponent->SetupAttachment(VRCameraAdjuster);
	this->RightHandComponent->SetupAttachment(VRCameraAdjuster);
	this->PadMotionComponent->SetupAttachment(VRCameraAdjuster);
	this->LeftHandTrigger->SetupAttachment(LeftHandComponent);
	this->RightHandTrigger->SetupAttachment(RightHandComponent);
	this->PadTrigger->SetupAttachment(PadMotionComponent);
	this->LeftAttachPoint->SetupAttachment(LeftHandComponent);
	this->RightAttachPoint->SetupAttachment(RightHandComponent);
	this->PadAttachPoint->SetupAttachment(PadMotionComponent);
}

void ASWGVRCharacter::StopFrameCounters() {
}

void ASWGVRCharacter::StartFrameCounters() {
}

void ASWGVRCharacter::SetVRModeEnabled(bool enable) {
}

void ASWGVRCharacter::SetHeldOffset(EVRHandType Hand, const FVector& NewOffset, int32 ItemIndex) {
}

void ASWGVRCharacter::SetCameraWorldRotation(const FRotator& Rotation) {
}

void ASWGVRCharacter::SetCameraWorldLocationAndRotation(const FVector& Location, const FRotator& Rotation) {
}

void ASWGVRCharacter::SetCameraWorldLocation(const FVector& Location) {
}

void ASWGVRCharacter::SetCameraRelativeRotation(const FRotator& Rotation) {
}

void ASWGVRCharacter::SetCameraRelativeLocationAndRotation(const FVector& Location, const FRotator& Rotation) {
}

void ASWGVRCharacter::SetCameraRelativeLocation(const FVector& Location) {
}

void ASWGVRCharacter::ReleaseGrabbable(AActor* Grabbable, bool bForce, bool bOverrideVelocity, FVector Velocity) {
}

void ASWGVRCharacter::ReleaseAll(EVRHandType Hand, bool bForce, bool bOverrideVelocity, FVector Velocity) {
}

void ASWGVRCharacter::ProcessInterpolatedGrab_Implementation(const FTransform& AttachmentTransform, FHeldGrabbableInfo& ActorGrabbablePair, AActor* HeldActor, EVRHandType Hand) {
}

void ASWGVRCharacter::OnTrackedControllerChanged_Implementation() {
}

void ASWGVRCharacter::OnRightEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
}

void ASWGVRCharacter::OnRightBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
}

void ASWGVRCharacter::OnRelease_Implementation(AActor* Grabbable, EVRHandType Hand) {
}

void ASWGVRCharacter::OnLeftEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
}

void ASWGVRCharacter::OnLeftBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
}

void ASWGVRCharacter::OnHoverEnd_Implementation(AActor* HoveredActor, EVRHandType Hand) {
}

void ASWGVRCharacter::OnHoverBegin_Implementation(AActor* HoveredActor, EVRHandType Hand) {
}

void ASWGVRCharacter::OnHeldActorDestroyed(AActor* DestroyedActor) {
}

void ASWGVRCharacter::OnGrabHoverEnd_Implementation(AActor* Grabbable, EVRHandType Hand) {
}

void ASWGVRCharacter::OnGrabHoverBegin_Implementation(AActor* Grabbable, EVRHandType Hand) {
}

void ASWGVRCharacter::OnGrab_Implementation(AActor* Grabbable, EVRHandType Hand) {
}

bool ASWGVRCharacter::IsUsingPad() const {
	return false;
}

bool ASWGVRCharacter::IsInVRMode() const {
	return false;
}

bool ASWGVRCharacter::InitialIsInVR() const {
	return false;
}

void ASWGVRCharacter::GrabGrabbable(AActor* Grabbable, EVRHandType Hand, bool bForce) {
}

FName ASWGVRCharacter::GetPadTrackingSource() const {
	return NAME_None;
}

FMotionControllerInfo& ASWGVRCharacter::GetHandInfo(EVRHandType Hand)
{
	static FMotionControllerInfo EmptyControllerInfo;
	
	if (Hand == EVRHandType::Left)
		return LeftController;
	if (Hand == EVRHandType::Right)
		return RightController;
	
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


EVRHandType ASWGVRCharacter::GetHandForPad() const {
	return EVRHandType::None;
}

USceneComponent* ASWGVRCharacter::GetHandAttachPoint(EVRHandType Hand) const {
	return NULL;
}

ESWGVRControllerType ASWGVRCharacter::GetControllerDeviceType() const {
	return ESWGVRControllerType::SteamVR;
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
