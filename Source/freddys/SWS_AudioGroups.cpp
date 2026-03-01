#include "SWS_AudioGroups.h"
#include "SWS_GroupComponent.h"

ASWS_AudioGroups::ASWS_AudioGroups(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	this->AudioGroupComponent = CreateDefaultSubobject<USWS_GroupComponent>(TEXT("GroupComponent"));
}


