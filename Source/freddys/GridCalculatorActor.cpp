#include "GridCalculatorActor.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"

AGridCalculatorActor::AGridCalculatorActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GridWidth = 10;
	GridHeight = 10;
	GridCellSize = 100.f;
	bShowDebug = false;
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
}

void AGridCalculatorActor::BeginPlay()
{
	int GridSize = GridHeight * GridWidth;

	PassabilityMap.SetNum(GridSize);
	Distances.SetNum(GridSize);

	ResetDistances();

	const FVector ForwardVec = GetActorForwardVector();
	const FVector RightVec = GetActorRightVector();
	const FVector WorldLoc = GetActorLocation();

	// Probably wrong, TODO diff
	
	auto CalcPosition = [this, ForwardVec, RightVec, WorldLoc](int32 X, int32 Y)
	{
		const float Cell = GridCellSize;
		return WorldLoc + ForwardVec * (X * Cell) + RightVec * (Y * Cell);
	};

	auto CheckCell = [this, CalcPosition](int32 X, int32 Y)
	{
		FHitResult Hit;

		FVector A = CalcPosition(X, Y);
		FVector B = CalcPosition(X + 1, Y);
		FVector C = CalcPosition(X + 1, Y + 1);
		FVector D = CalcPosition(X, Y + 1);

		bool b0 = !GetWorld()->LineTraceSingleByChannel(Hit, A, B, ECC_Visibility);
		bool b1 = !GetWorld()->LineTraceSingleByChannel(Hit, B, C, ECC_Visibility);
		bool b2 = !GetWorld()->LineTraceSingleByChannel(Hit, C, D, ECC_Visibility);
		bool b3 = !GetWorld()->LineTraceSingleByChannel(Hit, D, A, ECC_Visibility);

		return (uint32)b0 | (uint32)b1 << 8 | (uint32)b2 << 16 | (uint32)b3 << 24;
	};

	for (int32 X = 0; X < GridWidth; ++X)
	{
		for (int32 Y = 0; Y < GridHeight; ++Y)
		{
			PassabilityMap[X + Y * GridWidth] = CheckCell(X, Y);
		}
	}
	
	Super::BeginPlay();
}

void AGridCalculatorActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Unused
}

void AGridCalculatorActor::ResetDistances() 
{
	for (int& Distance : Distances)
	{
		Distance = INT_MAX;
	}
}

int32 AGridCalculatorActor::GetDistanceToCellAtWorldPosition(const FVector& WorldPosition) const 
{
	int CellIDFromWorldPosition = GetCellIDFromWorldPosition(WorldPosition);
	return GetDistanceToCell(CellIDFromWorldPosition); // Inlined in exe
}

int32 AGridCalculatorActor::GetDistanceToCell(int32 CellID) const
{
	if (Distances.IsValidIndex(CellID))
		return Distances[CellID];

	return UINT_MAX;

	// Inlined IsValidIndex

	//if (CellID < 0 || CellID >= Distances.Num())
	//	return UINT_MAX;
	//else
	//	return Distances[CellID];
}

FVector AGridCalculatorActor::GetCellWorldPositionByCellPos(int32 CellX, int32 CellY) const 
{
	FVector GridPos = FVector{ CellX * GridCellSize, CellY * GridCellSize, 0.f };
	return GetActorTransform().TransformPositionNoScale(GridPos);
}

FVector AGridCalculatorActor::GetCellWorldPosition(int32 CellID) const 
{
	int CellX, CellY;
	GetCellPosition(CellID, CellX, CellY);

	return GetCellWorldPositionByCellPos(CellX, CellY);
}

TArray<int32> AGridCalculatorActor::GetCellsBetweenDistances(int32 MinDistance, int32 MaxDistance) const 
{
	TArray<int32> CellsBetween = {};
	if (GridHeight * GridWidth > 0)
	{
		for (int Cell = 0; Cell < GridHeight * GridWidth; Cell++)
		{
			if (Cell >= MinDistance && Cell <= MaxDistance)
			{
				CellsBetween.Add(Cell);
			}
		}
	}

	return CellsBetween;
}

TArray<int32> AGridCalculatorActor::GetCellsAtDistance(int32 Distance) const 
{
	TArray<int32> CellsAt = {};
	if (GridHeight * GridWidth > 0)
	{
		for (int Cell = 0; Cell < GridHeight * GridWidth; Cell++)
		{
			if (Distances[Cell] == Distance)
			{
				CellsAt.Add(Cell);
			}
		}
	}

	return CellsAt;
}

void AGridCalculatorActor::GetCellPosition(int32 CellID, int32& CellX, int32& CellY) const 
{
	CellX = CellID % GridWidth;
	CellY = CellID / GridWidth;
}

void AGridCalculatorActor::GetCellPosFromWorldPosition(const FVector& WorldPosition, int32& CellX, int32& CellY) const 
{
	FVector InversedWorldPos = GetActorTransform().InverseTransformPositionNoScale(WorldPosition);
	CellX = (InversedWorldPos.X + (GridCellSize * 0.5f)) / GridCellSize;
	CellY = (InversedWorldPos.Y + (GridCellSize * 0.5f)) / GridCellSize;
}

int32 AGridCalculatorActor::GetCellIDFromWorldPosition(const FVector& WorldPosition) const 
{
	int CellX, CellY;
	GetCellPosFromWorldPosition(WorldPosition, CellX, CellY);

	int CellId = CellX + (GridWidth * CellY);
	if (Distances.IsValidIndex(CellId))
		return CellId;

	return UINT_MAX;
}

int32 AGridCalculatorActor::GetCellIDFromGridPosition(int32 CellX, int32 CellY) const 
{
	if (CellX < 0)
		return UINT_MAX;

	if (CellY < 0)
		return UINT_MAX;

	if (CellX >= GridWidth || CellY >= GridHeight)
		return UINT_MAX;

	return CellX + CellY * GridWidth;
}

TArray<int32> AGridCalculatorActor::FindPathFromWorldPositions(const FVector& WorldPositionStart, const FVector& WorldPositionEnd) const 
{
	TArray<int32> Path{};
	GetCellIDFromGridPosition(WorldPositionEnd.X, WorldPositionEnd.Y);

	// What has happened here FindPathFromWorldPositions

	//v4 = 1.0 / this->GridCellSize;
	//v5 = (int)(float)(v4 * WorldPositionEnd->X);
	//v6 = (int)(float)(v4 * WorldPositionEnd->Y);
	//if (v5 < 0 || v6 < 0 || v5 >= this->GridWidth || v6 >= this->GridHeight)
	//{
	//	result->AllocatorInstance.Data = 0;
	//	result->ArrayNum = 0;
	//	result->ArrayMax = 0;
	//	return result;
	//}
	//else
	//{
	//	result->AllocatorInstance.Data = 0;
	//	result->ArrayNum = 0;
	//	result->ArrayMax = 0;
	//	return result;
	//}

	return Path;
}

TArray<int32> AGridCalculatorActor::FindPathFromCellIDs(int32 StartCellID, int32 EndCellID) const 
{
	// Probably wrong, ruby check later 1406A0450
	if (Distances.IsValidIndex(StartCellID))
		return Distances;

	return TArray<int32>();
}

void AGridCalculatorActor::CalculateDistancesFromWorldPosition(const FVector& WorldPosition) 
{
	int CellX, CellY;
	GetCellPosFromWorldPosition(WorldPosition, CellX, CellY);

	CalculateDistancesFromGridPosition(CellX, CellY);
}

void AGridCalculatorActor::CalculateDistancesFromGridPosition(int32 GridX, int32 GridY) 
{
	ResetDistances();

	if (GridX >= 0 && GridY >= 0)
	{
		if (GridX < GridWidth && GridY < GridHeight)
		{
			struct VisitNode
			{
				int x;
				int y;
			};

			TArray<VisitNode> NodesToVisit{};
			Distances[GridX + GridY * GridWidth] = 0;

			NodesToVisit.Push({ GridY, GridX });

			for (int NodeIdx = 0; NodeIdx > 0; NodeIdx++)
			{
				// TODO: Finish this function

				NodesToVisit.RemoveAt(NodeIdx);
			}
		}
	}
}