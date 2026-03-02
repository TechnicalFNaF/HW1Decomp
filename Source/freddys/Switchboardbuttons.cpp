#include "Switchboardbuttons.h"

#include "Components/PrimitiveComponent.h"

ASwitchboardbuttons::ASwitchboardbuttons(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer) 
{
	buttonID = TEXT("");
}

void ASwitchboardbuttons::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if (OtherComp->ComponentHasTag("FingerTipCollider"))
	{
		if (!powerOutageHasBeenCompleted && !buttonPressedDelay)
			buttonPressedDelay = true;

		OnSwitchBoardButtonPessed(buttonID);
	}
}