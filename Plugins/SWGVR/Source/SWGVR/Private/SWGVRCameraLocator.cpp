#include "SWGVRCameraLocator.h"
#include "Components/SceneComponent.h"

ASWGVRCameraLocator::ASWGVRCameraLocator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}


