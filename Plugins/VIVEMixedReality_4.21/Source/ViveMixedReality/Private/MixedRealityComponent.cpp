#include "MixedRealityComponent.h"

AMixedRealityComponent::AMixedRealityComponent(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer) 
{
}

AMixedRealityComponent::~AMixedRealityComponent()
{
}

void AMixedRealityComponent::init(AActor* target, APlayerCameraManager* character, FLinearColor chromacolor)
{
}

void AMixedRealityComponent::StartMixedReality(int32 trackerID)
{
}

void AMixedRealityComponent::StopMixedReality()
{
}

bool AMixedRealityComponent::LoadConfig()
{
	return false;
}

bool AMixedRealityComponent::SetupCapture()
{
	return false;
}

void AMixedRealityComponent::BeginPlay()
{
	Super::BeginPlay();
	Log(TEXT("*** MixedRealityComponent: BeginPlay"));
	SetActorTickEnabled(false);
	//SetupCapture();
}

void AMixedRealityComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AMixedRealityComponent::ShouldTickIfViewportsOnly() const
{
	return true;
}

bool AMixedRealityComponent::FileLoadString(FString FileNameA, FString& SaveTextA)
{
	return false;
}

void AMixedRealityComponent::Log(FString pString)
{
	UE_LOG(LogTemp, Display, TEXT("%s"), *pString);
}