#include "Switchboardbuttons.h"

#include "Components/PrimitiveComponent.h"

// Matching
ASwitchboardbuttons::ASwitchboardbuttons()
{
	// Does nothing
}

// Matching
void ASwitchboardbuttons::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if (OtherComp->ComponentHasTag("FingerTipCollider"))
	{
		if (!powerOutageHasBeenCompleted && !buttonPressedDelay)
			buttonPressedDelay = true;

		OnSwitchBoardButtonPessed(buttonID);
	}
}