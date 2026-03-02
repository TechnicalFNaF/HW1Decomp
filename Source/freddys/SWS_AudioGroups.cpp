#include "SWS_AudioGroups.h"
#include "SWS_GroupComponent.h"

ASWS_AudioGroups::ASWS_AudioGroups(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer) 
{
	AudioGroupComponent = CreateDefaultSubobject<USWS_GroupComponent>("GroupComponent");
	PrimaryActorTick.bCanEverTick = true;
	GroupID = 0;
}

void ASWS_AudioGroups::BeginPlay()
{
	Super::BeginPlay();

	if (AudioGroupComponent)
		AudioGroupComponent->Initialize(GroupID);
}

void ASWS_AudioGroups::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Unused override
}