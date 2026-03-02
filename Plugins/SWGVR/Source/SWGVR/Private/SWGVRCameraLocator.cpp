#include "SWGVRCameraLocator.h"

#include "Kismet/GameplayStatics.h"

ASWGVRCameraLocator::ASWGVRCameraLocator()
{
    PrimaryActorTick.bCanEverTick = true;
    
    USceneComponent* NewRoot = CreateDefaultSubobject<USceneComponent>("Root");
    Root = NewRoot;
    SetRootComponent(NewRoot);

    ForwardArrow = CreateDefaultSubobject<UArrowComponent>("VRWorldForward");
    ForwardArrow->SetupAttachment(Root);
    ForwardArrow->SetArrowColor(FLinearColor::Red);
    
    RightArrow = CreateDefaultSubobject<UArrowComponent>("VRWorldRight");
    RightArrow->SetupAttachment(Root);
    RightArrow->SetRelativeRotation(FRotator::MakeFromEuler({0,0,90}));
    RightArrow->SetArrowColor(FLinearColor::Blue);
}

void ASWGVRCameraLocator::BeginPlay()
{
    // lol
    UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    Super::BeginPlay();
}
