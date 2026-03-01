#include "GridCalculatorActor.h"
#include "Components/SceneComponent.h"

AGridCalculatorActor::AGridCalculatorActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->Root = (USceneComponent*)RootComponent;
	this->GridWidth = 10;
	this->GridHeight = 10;
	this->GridCellSize = 100.00f;
	this->bShowDebug = false;
}


void AGridCalculatorActor::ResetDistances() {
}

void AGridCalculatorActor::GetGridSize(int32& Width, int32& Height) const {
}

int32 AGridCalculatorActor::GetDistanceToCellAtWorldPosition(const FVector& WorldPosition) const {
	return 0;
}

int32 AGridCalculatorActor::GetDistanceToCell(int32 CellID) const {
	return 0;
}

FVector AGridCalculatorActor::GetCellWorldPositionByCellPos(int32 CellX, int32 CellY) const {
	return FVector{};
}

FVector AGridCalculatorActor::GetCellWorldPosition(int32 CellID) const {
	return FVector{};
}

TArray<int32> AGridCalculatorActor::GetCellsBetweenDistances(int32 MinDistance, int32 MaxDistance) const {
	return TArray<int32>();
}

TArray<int32> AGridCalculatorActor::GetCellsAtDistance(int32 Distance) const {
	return TArray<int32>();
}

void AGridCalculatorActor::GetCellPosition(int32 CellID, int32& CellX, int32& CellY) const {
}

void AGridCalculatorActor::GetCellPosFromWorldPosition(const FVector& WorldPosition, int32& CellX, int32& CellY) const {
}

int32 AGridCalculatorActor::GetCellIDFromWorldPosition(const FVector& WorldPosition) const {
	return 0;
}

int32 AGridCalculatorActor::GetCellIDFromGridPosition(int32 CellX, int32 CellY) const {
	return 0;
}

TArray<int32> AGridCalculatorActor::FindPathFromWorldPositions(const FVector& WorldPositionStart, const FVector& WorldPositionEnd) const {
	return TArray<int32>();
}

TArray<int32> AGridCalculatorActor::FindPathFromCellIDs(int32 StartCellID, int32 EndCellID) const {
	return TArray<int32>();
}

void AGridCalculatorActor::CalculateDistancesFromWorldPosition(const FVector& WorldPosition) {
}

void AGridCalculatorActor::CalculateDistancesFromGridPosition(int32 GridX, int32 GridY) {
}


