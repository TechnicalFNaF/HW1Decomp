#include "SWS_AudioGroups.h"
#include "SWS_GroupComponent.h"

// Matching
ASWS_AudioGroups::ASWS_AudioGroups(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer) 
{
	USWS_GroupComponent* GroupComponent = CreateDefaultSubobject<USWS_GroupComponent>("GroupComponent");
	PrimaryActorTick.bCanEverTick = true;
	AudioGroupComponent = GroupComponent;
	GroupID = 0;
}

// Matching
void ASWS_AudioGroups::BeginPlay()
{
	Super::BeginPlay();
	if (AudioGroupComponent)
	{
		AudioGroupComponent->Initialize(GroupID);
	}
}
