#pragma once

#include "CoreMinimal.h"
#include "AsyncWork.h"
#include "Kismet/GameplayStatics.h"

struct FSaveGameTask : FNonAbandonableTask
{
	USaveGame* SaveGameToStore;
	FString SlotNameToStore;
	int UserIndexToStore;

	FSaveGameTask(USaveGame* InSaveGameToStore, const FString& InSlotNameToStore, int InUserIndexToStore)
		: SaveGameToStore(InSaveGameToStore), SlotNameToStore(InSlotNameToStore), UserIndexToStore(InUserIndexToStore)
	{
	}

	// Matching
	void DoWork()
	{
		UGameplayStatics::SaveGameToSlot(SaveGameToStore, SlotNameToStore, UserIndexToStore);
	}

	// Matching
	void Abandon()
	{
		DoWork();
	}
	
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FSaveGameTask, STATGROUP_ThreadPoolAsyncTasks);
	}
};
