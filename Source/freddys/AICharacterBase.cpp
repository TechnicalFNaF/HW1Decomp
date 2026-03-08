#include "AICharacterBase.h"

// Matching
AAICharacterBase::AAICharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Matching
void AAICharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Matching
void AAICharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
