#include "GridCalculatorActor.h"
#include "Components/SceneComponent.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

// Matching
AGridCalculatorActor::AGridCalculatorActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = Root = CreateDefaultSubobject<USceneComponent>("Root");
}

// TODO Not matching
void AGridCalculatorActor::BeginPlay()
{
	int GridSize = GridHeight * GridWidth;

	PassabilityMap.SetNum(GridSize);
	Distances.SetNum(GridSize);

	ResetDistances();

	const FVector XAxis = GetActorForwardVector();
	const FVector YAxis = GetActorRightVector();
	const FVector WorldLocation = GetActorLocation();

	auto CalcPosition = [XAxis, YAxis, WorldLocation, this](int32 X, int32 Y)
	{
		const float Cell = GridCellSize;
		return WorldLocation + X * Cell * XAxis + Y * Cell * YAxis;
	};

	auto CheckCell = [this, CalcPosition](int32 StartX, int32 StartY, int32 EndX, int32 EndY) -> uint8
	{
		FHitResult Hit;
		FVector Start = CalcPosition(StartX, StartY);
		FVector End = CalcPosition(EndX, EndY);
		return !GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);
	};

	for (int32 X = 0; X < GridWidth; ++X)
	{
		for (int32 Y = 0; Y < GridHeight; ++Y)
		{
			uint8 A = CheckCell(X,   Y,   X+1, Y  );
			uint8 B = CheckCell(X+1, Y,   X+1, Y+1);
			uint8 C = CheckCell(X+1, Y+1, X,   Y+1);
			uint8 D = CheckCell(X,   Y+1, X,   Y  );

			PassabilityMap[X + Y * GridWidth] = A | (B << 8) | (C << 16) | (D << 24);
		}
	}
	
	Super::BeginPlay();
}

// Matching
void AGridCalculatorActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

// Matching
void AGridCalculatorActor::ResetDistances() 
{
	for (int& Distance : Distances)
	{
		Distance = INT_MAX;
	}
}

// Matching
int32 AGridCalculatorActor::GetDistanceToCellAtWorldPosition(const FVector& WorldPosition) const 
{
	int CellIDFromWorldPosition = GetCellIDFromWorldPosition(WorldPosition);
	return GetDistanceToCell(CellIDFromWorldPosition);
}

// Matching
int32 AGridCalculatorActor::GetDistanceToCell(int32 CellID) const
{
	if (Distances.IsValidIndex(CellID))
		return Distances[CellID];

	return -1;
}

// Matching
FVector AGridCalculatorActor::GetCellWorldPositionByCellPos(int32 CellX, int32 CellY) const 
{
	FVector GridPos = FVector{ CellX * GridCellSize, CellY * GridCellSize, 0.f };
	return GetTransform().TransformPositionNoScale(GridPos);
}

// Matching
FVector AGridCalculatorActor::GetCellWorldPosition(int32 CellID) const 
{
	int CellX, CellY;
	GetCellPosition(CellID, CellX, CellY);
	return GetCellWorldPositionByCellPos(CellX, CellY);
}

// TODO Not matching, functionally identical
TArray<int32> AGridCalculatorActor::GetCellsBetweenDistances(int32 MinDistance, int32 MaxDistance) const 
{
	TArray<int32> CellsBetween = {};
	for (int i = 0; i < GridHeight * GridWidth; i++)
	{
		int32 Cell = Distances[i];
		if (Cell >= MinDistance && Cell <= MaxDistance)
		{
			CellsBetween.Add(Cell);
		}
	}
	return CellsBetween;
}

// Matching
TArray<int32> AGridCalculatorActor::GetCellsAtDistance(int32 Distance) const 
{
	TArray<int32> CellsAt = {};
	for (int Cell = 0; Cell < GridHeight * GridWidth; Cell++)
	{
		if (Distances[Cell] == Distance)
		{
			CellsAt.Add(Cell);
		}
	}
	return CellsAt;
}

// Matching
void AGridCalculatorActor::GetCellPosition(int32 CellID, int32& CellX, int32& CellY) const 
{
	CellX = CellID % GridWidth;
	CellY = CellID / GridWidth;
}

// Matching
void AGridCalculatorActor::GetCellPosFromWorldPosition(const FVector& WorldPosition, int32& CellX, int32& CellY) const 
{
	FVector InversedWorldPos = GetTransform().InverseTransformPositionNoScale(WorldPosition);
	CellX = (InversedWorldPos.X + (GridCellSize * 0.5f)) / GridCellSize;
	CellY = (InversedWorldPos.Y + (GridCellSize * 0.5f)) / GridCellSize;
}

// Matching
int32 AGridCalculatorActor::GetCellIDFromWorldPosition(const FVector& WorldPosition) const
{
	int CellX, CellY;
	GetCellPosFromWorldPosition(WorldPosition, CellX, CellY);

	int CellId = CellX + (GridWidth * CellY);
	return Distances.IsValidIndex(CellId) ? CellId : -1;
}

// Matching
int32 AGridCalculatorActor::GetCellIDFromGridPosition(int32 CellX, int32 CellY) const 
{
	if (CellX < 0)
		return -1;

	if (CellY < 0)
		return -1;

	if (CellX >= GridWidth || CellY >= GridHeight)
		return -1;

	return CellX + CellY * GridWidth;
}

// TODO Not matching, functionally identical
TArray<int32> AGridCalculatorActor::FindPathFromWorldPositions(const FVector& WorldPositionStart, const FVector& WorldPositionEnd) const 
{
	if (GetCellIDFromGridPosition(WorldPositionEnd.X, WorldPositionEnd.Y) < 0)
	{
		int og = GetCellIDFromGridPosition(WorldPositionEnd.X, WorldPositionEnd.Y);
		return {};
	}
	return {};
}

// TODO Not matching, functionally identical
TArray<int32> AGridCalculatorActor::FindPathFromCellIDs(int32 StartCellID, int32 EndCellID) const 
{
	TArray<int32> Out;
	if (Out.IsValidIndex(StartCellID))
	{
		Distances;
	}
	return Out;
}

// Matching
void AGridCalculatorActor::CalculateDistancesFromWorldPosition(const FVector& WorldPosition) 
{
	int CellX, CellY;
	GetCellPosFromWorldPosition(WorldPosition, CellX, CellY);
	CalculateDistancesFromGridPosition(CellX, CellY);
}

// TODO Not matching
void AGridCalculatorActor::CalculateDistancesFromGridPosition(int32 GridX, int32 GridY) 
{
	ResetDistances();

	if (GridX >= 0 && GridY >= 0 && GridX < GridWidth && GridY < GridHeight)
	{
		struct VisitNode
		{
			int x;
			int y;
		};

		TArray<VisitNode> NodesToVisit;
		Distances[GridX + GridY * GridWidth] = 0;

		NodesToVisit.Push({ GridX, GridY });

		while (NodesToVisit.Num() > 0)
		{
			VisitNode node = NodesToVisit[0];

			int nextVal = (node.x + node.y * GridWidth) + 1;
			const int CellPassability = PassabilityMap[node.x + node.y * GridWidth];

			auto cfb = [node, this, nextVal, &NodesToVisit, CellPassability](int32 X, int32 Y, uint32 Mask)
			{
				int Distance = GridWidth * ((node.x + X) + (node.y + Y));
				if ((CellPassability & Mask) != false)
				{
					if (nextVal < Distances[Distance])
					{
						Distances[Distance] = nextVal;
						NodesToVisit.Add({ node.x + X, node.y + Y });
					}
				}
			};
				
			if (node.y < GridHeight - 1)
				cfb(0, 0, 0x0000FF00);

			if (node.x < GridHeight - 1)
				cfb(1, 0, 0x000000FF);

			if (node.y > 0)
				cfb(0, -1, 0xFF000000);

			if (node.x > 0)
				cfb(-1, 0, 0x00FF0000);

			NodesToVisit.RemoveAt(0);
		}
	}
}