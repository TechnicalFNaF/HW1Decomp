#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Character.h"
#include "Engine/EngineTypes.h"
#include "HeadMountedDisplayTypes.h"
#include "ESWGVRControllerType.h"
#include "EVRHandType.h"
#include "HeldGrabbableInfo.h"
#include "MotionControllerInfo.h"
#include "OnControllerTrackingChangedDelegate.h"
#include "OnGrabbableEventDelegate.h"
#include "SWGVRCharacter.generated.h"

class AActor;
class UArrowComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UPrimitiveComponent;
class USceneComponent;
class USphereComponent;

UCLASS()
class SWGVR_API ASWGVRCharacter : public ACharacter {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable)
    FOnControllerTrackingChanged OnControllerTrackingChanged;
    
    UPROPERTY(BlueprintAssignable)
    FOnControllerTrackingChanged OnControllerDeviceChanged;
    
    UPROPERTY(BlueprintAssignable)
    FOnGrabbableEvent OnActorGrabbed;
    
    UPROPERTY(BlueprintAssignable)
    FOnGrabbableEvent OnActorReleased;
    
protected:
    UPROPERTY(BlueprintReadOnly, Instanced, VisibleAnywhere)
    UCameraComponent* CameraComp;
    
    UPROPERTY(BlueprintReadOnly, Instanced, VisibleAnywhere)
    USceneComponent* VROriginComp;
    
    UPROPERTY(BlueprintReadOnly, Instanced, VisibleAnywhere)
    USceneComponent* VRCameraAdjuster;
    
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
    bool bPositionalHeadTracking;
    
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced)
    UMotionControllerComponent* LeftHandComponent;
    
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced)
    UMotionControllerComponent* RightHandComponent;
    
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced)
    UMotionControllerComponent* PadMotionComponent;
    
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced)
    USphereComponent* LeftHandTrigger;
    
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced)
    USphereComponent* RightHandTrigger;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced)
    USphereComponent* PadTrigger;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced)
    USceneComponent* LeftAttachPoint;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced)
    USceneComponent* RightAttachPoint;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced)
    USceneComponent* PadAttachPoint;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced)
    UArrowComponent* PadInteractionPointer;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    EVRHandType HandsThatGrab;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FName LeftGrabActionName;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FName RightGrabActionName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float ThrowMagnitude;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    bool bGrabClosest;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    bool bHoldMultiple;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    EVRHandType HandsThatInteract;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FName LeftInteractActionName;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FName RightInteractActionName;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    TEnumAsByte<EHMDTrackingOrigin::Type> VRTrackingOrigin;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    bool bUseEyeOffsetForEyeTracking;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    float EyeOffset;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    bool bUseHandForPad;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    EVRHandType HandToUseAsPad;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float PadLineTraceDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float LerpGrabSpeed;
    
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    bool bPerfCounterEnabled;
    
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    float FPSMin;
    
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    float FPSMax;
    
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    float FPSAverageOverTime;
    
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    float FPSImmediate;
    
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    float PerfCounterSeconds;
    
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    float PerfCounterImmediateSeconds;
    
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    float TotalPerfSeconds;
    
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    int32 FrameCounterForAverage;
    
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    bool VRModeEnabled;
    
public:
    ASWGVRCharacter(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void StopFrameCounters();
    
    UFUNCTION(BlueprintCallable)
    void StartFrameCounters();
    
    UFUNCTION(BlueprintCallable)
    void SetVRModeEnabled(bool enable);
    
    UFUNCTION(BlueprintCallable)
    void SetHeldOffset(EVRHandType Hand, const FVector& NewOffset, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void SetCameraWorldRotation(const FRotator& Rotation);
    
    UFUNCTION(BlueprintCallable)
    void SetCameraWorldLocationAndRotation(const FVector& Location, const FRotator& Rotation);
    
    UFUNCTION(BlueprintCallable)
    void SetCameraWorldLocation(const FVector& Location);
    
    UFUNCTION(BlueprintCallable)
    void SetCameraRelativeRotation(const FRotator& Rotation);
    
    UFUNCTION(BlueprintCallable)
    void SetCameraRelativeLocationAndRotation(const FVector& Location, const FRotator& Rotation);
    
    UFUNCTION(BlueprintCallable)
    void SetCameraRelativeLocation(const FVector& Location);
    
    UFUNCTION(BlueprintCallable)
    void ReleaseGrabbable(AActor* Grabbable, bool bForce, bool bOverrideVelocity, FVector Velocity);
    
    UFUNCTION(BlueprintCallable)
    void ReleaseAll(EVRHandType Hand, bool bForce, bool bOverrideVelocity, FVector Velocity);
    
protected:
    UFUNCTION(BlueprintNativeEvent)
    void ProcessInterpolatedGrab(const FTransform& AttachmentTransform, UPARAM(Ref) FHeldGrabbableInfo& ActorGrabbablePair, AActor* HeldActor, EVRHandType Hand);
    
    UFUNCTION(BlueprintNativeEvent)
    void OnTrackedControllerChanged();
    
private:
    UFUNCTION()
    void OnRightEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
    UFUNCTION()
    void OnRightBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
protected:
    UFUNCTION(BlueprintNativeEvent)
    void OnRelease(AActor* Grabbable, EVRHandType Hand);
    
private:
    UFUNCTION()
    void OnLeftEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
    UFUNCTION()
    void OnLeftBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
protected:
    UFUNCTION(BlueprintNativeEvent)
    void OnHoverEnd(AActor* HoveredActor, EVRHandType Hand);
    
    UFUNCTION(BlueprintNativeEvent)
    void OnHoverBegin(AActor* HoveredActor, EVRHandType Hand);
    
private:
    UFUNCTION()
    void OnHeldActorDestroyed(AActor* DestroyedActor);
    
protected:
    UFUNCTION(BlueprintNativeEvent)
    void OnGrabHoverEnd(AActor* Grabbable, EVRHandType Hand);
    
    UFUNCTION(BlueprintNativeEvent)
    void OnGrabHoverBegin(AActor* Grabbable, EVRHandType Hand);
    
    UFUNCTION(BlueprintNativeEvent)
    void OnGrab(AActor* Grabbable, EVRHandType Hand);
    
public:
    UFUNCTION(BlueprintPure)
    bool IsUsingPad() const;
    
    UFUNCTION(BlueprintPure)
    bool IsInVRMode() const;
    
    UFUNCTION()
    bool InitialIsInVR() const;
    
    UFUNCTION(BlueprintCallable)
    void GrabGrabbable(AActor* Grabbable, EVRHandType Hand, bool bForce);
    
    UFUNCTION(BlueprintPure)
    FName GetPadTrackingSource() const;
    
    UFUNCTION(BlueprintPure)
    FVector GetHeldOffset(EVRHandType Hand, int32 ItemIndex) const;
    
    UFUNCTION(BlueprintPure)
    FMotionControllerInfo GetHandInfo(EVRHandType Hand) const;
    
    UFUNCTION(BlueprintPure)
    EVRHandType GetHandForPad() const;
    
    UFUNCTION(BlueprintPure)
    USceneComponent* GetHandAttachPoint(EVRHandType Hand) const;
    
    UFUNCTION(BlueprintPure)
    FHeldGrabbableInfo GetGrabbableInfo(const AActor* HeldActor) const;
    
    UFUNCTION(BlueprintPure)
    ESWGVRControllerType GetControllerDeviceType() const;
    
    UFUNCTION(BlueprintCallable)
    void AddHeldOffset(EVRHandType Hand, const FVector& AdditiveValue, int32 ItemIndex);
    
};

