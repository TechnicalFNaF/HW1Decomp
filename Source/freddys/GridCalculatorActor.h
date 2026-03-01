#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "GridCalculatorActor.generated.h"

UCLASS()
class FREDDYS_API AGridCalculatorActor : public AActor 
{
	GENERATED_BODY()
	
public:

	AGridCalculatorActor(const FObjectInitializer& ObjectInitializer);

protected:
	
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void ResetDistances();

	UFUNCTION(BlueprintPure)
	TArray<int32> FindPathFromWorldPositions(const FVector& WorldPositionStart, const FVector& WorldPositionEnd) const;

	UFUNCTION(BlueprintPure)
	TArray<int32> FindPathFromCellIDs(int32 StartCellID, int32 EndCellID) const;

	UFUNCTION(BlueprintCallable)
	void CalculateDistancesFromWorldPosition(const FVector& WorldPosition);
	
	UFUNCTION(BlueprintCallable)
	void CalculateDistancesFromGridPosition(int32 GridX, int32 GridY);

	UFUNCTION(BlueprintImplementableEvent)
	void SetCellDebugDisplay(int32 CellID, int32 CellX, int32 CellY, int32 CellDistance);

	UFUNCTION(BlueprintPure)
	void GetGridSize(int32& Width, int32& Height) const
	{
		Width = GridWidth;
		Height = GridHeight;
	};

	UFUNCTION(BlueprintPure)
	int32 GetDistanceToCellAtWorldPosition(const FVector& WorldPosition) const;

	UFUNCTION(BlueprintPure)
	int32 GetDistanceToCell(int32 CellID) const;

	UFUNCTION(BlueprintPure)
	FVector GetCellWorldPositionByCellPos(int32 CellX, int32 CellY) const;

	UFUNCTION(BlueprintPure)
	FVector GetCellWorldPosition(int32 CellID) const;

	UFUNCTION(BlueprintPure)
	TArray<int32> GetCellsBetweenDistances(int32 MinDistance, int32 MaxDistance) const;

	UFUNCTION(BlueprintPure)
	TArray<int32> GetCellsAtDistance(int32 Distance) const;

	UFUNCTION(BlueprintPure)
	void GetCellPosition(int32 CellID, int32& CellX, int32& CellY) const;

	UFUNCTION(BlueprintPure)
	void GetCellPosFromWorldPosition(const FVector& WorldPosition, int32& CellX, int32& CellY) const;

	UFUNCTION(BlueprintPure)
	int32 GetCellIDFromWorldPosition(const FVector& WorldPosition) const;

	UFUNCTION(BlueprintPure)
	int32 GetCellIDFromGridPosition(int32 CellX, int32 CellY) const;

public:

	UPROPERTY(Instanced)
	USceneComponent* Root;

private:

	UPROPERTY(EditAnywhere)
	int32 GridWidth;

	UPROPERTY(EditAnywhere)
	int32 GridHeight;

	UPROPERTY(EditAnywhere)
	float GridCellSize;

	UPROPERTY(EditAnywhere)
	bool bShowDebug;

	UPROPERTY(Instanced, VisibleAnywhere)
	TArray<class UTextRenderComponent*> TextRenderers;

	TArray<int> PassabilityMap;
	TArray<int> Distances;
};

