#include "MixedRealityComponent.h"

#include "GameFramework/GameUserSettings.h"

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
	Log("*** MixedRealityComponent: StartMixedReality");
	SetupCapture();
	Tracker = trackerID;

	UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();
	GameUserSettings->SetScreenResolution(screenresolution);
	GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);

	GameUserSettings->ApplyResolutionSettings(true); // May be wrong

	// Sets things in SceneCaptureNear->PostProcessSettings
	// Sets things in SceneCaptureFar->PostProcessSettings
	//*((_BYTE*)this->SceneCaptureNear + 0x1DC) |= 0x20u;
	//*((_BYTE*)this->SceneCaptureFar + 0x1DC) |= 0x20u;

	UHeadMountedDisplayFunctionLibrary::SetSpectatorScreenMode(ESpectatorScreenMode::TexturePlusEye);
	SetActorTickEnabled(true);
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
	Log("*** MixedRealityComponent: BeginPlay");
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