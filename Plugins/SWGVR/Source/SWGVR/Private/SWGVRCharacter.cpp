#include "SWGVRCharacter.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "MotionControllerComponent.h"

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

#define NEW_INFINITY ((float)(_HUGE_ENUF * _HUGE_ENUF))

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

#undef NEW_INFINITY

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
