// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFinderBase.h"

#include "DrawDebugHelpers.h"
#include "MapCreator.h"
#include "Kismet/GameplayStatics.h"

UPathFinderBase::UPathFinderBase()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPathFinderBase::BeginPlay()
{
	Super::BeginPlay();

	AActor* mapCreator = UGameplayStatics::GetActorOfClass(this, AMapCreator::StaticClass());
	if (mapCreator)
	{
		MapInfoArray = Cast<AMapCreator>(mapCreator)->MapInfoArray;
	}
}

void UPathFinderBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPathFinderBase::FindPathOnce(int rowCurrent, int colCurrent, int rowTarget, int colTarget, float deltaTime)
{
	FindPathStart(rowCurrent, colCurrent, rowTarget, colTarget);
		
	GetOwner()->GetWorldTimerManager().ClearTimer(PathFinderTimerHandle);
	GetOwner()->GetWorldTimerManager().SetTimer(PathFinderTimerHandle, this, &UPathFinderBase::FindPathStep, deltaTime, true);
}

void UPathFinderBase::FindPath(int rowCurrent, int colCurrent, int rowTarget, int colTarget)
{
	FindPathStart(rowCurrent, colCurrent, rowTarget, colTarget);

	while(bFinding)
	{
		FindPathStep();
	}
}

void UPathFinderBase::FindPathStart(int rowCurrent, int colCurrent, int rowTarget, int colTarget)
{
	OpenSet.Empty();
	CloseSet.Empty();

	RowCurrent = rowCurrent;
	ColCurrent = colCurrent;
	RowTarget = rowTarget;
	ColTarget = colTarget;

	// 将起点加入OpenSet
	FPoint startPoint;
	startPoint.X = rowCurrent;
	startPoint.Y = colCurrent;
	OpenSet.Add(startPoint);

	bFinding = true;
}

void UPathFinderBase::FindPathStep()
{
	// UE_LOG(LogTemp, Log, TEXT("%s"), *FString(__FUNCTION__));
	int index = SelectPointInOpenList();
	if (index < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No path found, algorithm failed!!!"));
		return;
	}

	FPoint p = OpenSet[index];
	DrawDebugPoint(GetWorld(), FVector(p.X * 100, p.Y * 100, 0), 10, FColor::Blue, false, 3);

	if (IsEndPoint(p)) // 如果是终点，算法结束，构建路径
		{
		BuildPath(p);
		bFinding = false;
		GetOwner()->GetWorldTimerManager().ClearTimer(PathFinderTimerHandle);
		return;
		}

	// 将p移出OpenSet，移入CloseSet
	OpenSet.RemoveAt(index);
	CloseSet.Add(p);

	// Process all neighbors
	int x = p.X;
	int y = p.Y;
	// 可不能走对角线的
	ProcessPoint(x - 1, y, CloseSet.Num() - 1);
	ProcessPoint(x, y + 1, CloseSet.Num() - 1);
	ProcessPoint(x, y - 1, CloseSet.Num() - 1);
	ProcessPoint(x + 1, y, CloseSet.Num() - 1);
}

float UPathFinderBase::BaseCost(FPoint p)
{
	return 0;
}

float UPathFinderBase::HeuristicCost(FPoint p)
{
	return 0;
}

float UPathFinderBase::Cost(FPoint p)
{
	return BaseCost(p) + HeuristicCost(p);
}


bool UPathFinderBase::IsValidPoint(int x, int y)
{
	if (x < 0 || x > 74 || y < 0 || y > 74) return false;
	else if (!MapInfoArray[x * 75 + y].Equals("20")) return false;
	else return true;
}

bool UPathFinderBase::IsInPointList(FPoint p, TArray<FPoint> pointArray)
{
	for (FPoint point : pointArray)
	{
		if (point.X == p.X && point.Y == p.Y) return true;
	}
	return false;
}

bool UPathFinderBase::IsInOpenList(FPoint p)
{
	return IsInPointList(p, OpenSet);
}

bool UPathFinderBase::IsInCloseList(FPoint p)
{
	return IsInPointList(p, CloseSet);
}

bool UPathFinderBase::IsStartPoint(FPoint p)
{
	return p.X == RowCurrent && p.Y == ColCurrent;
}

bool UPathFinderBase::IsEndPoint(FPoint p)
{
	return p.X == RowTarget && p.Y == ColTarget;
}

int UPathFinderBase::SelectPointInOpenList()
{
	int index = -1;
	int minCost = 99999;
	for (int i = 0; i < OpenSet.Num(); i++)
	{
		int cost = Cost(OpenSet[i]);
		if (cost < minCost)
		{
			minCost = cost;
			index = i;
		}
	}

	return index;
}

void UPathFinderBase::ProcessPoint(int x, int y, int parentIndex)
{
	FPoint p;
	p.X = x;
	p.Y = y;

	if (!IsValidPoint(x, y) && !IsEndPoint(p)) return; // Do nothing for invalid point

	if (IsInCloseList(p)) return; // Do nothing for visited point
	if (!IsInOpenList(p))
	{
		p.ParentIndex = parentIndex;
		p.Cost = Cost(p);
		OpenSet.Add(p);

		DrawDebugPoint(GetWorld(), FVector(p.X * 100, p.Y * 100, 0), 10, FColor::Red, false,3);
	}
}

void UPathFinderBase::BuildPath(FPoint p)
{
	PathRes.Empty();
	FPoint point = p;
	PathRes.Add(p);

	while (true)
	{
		if (IsStartPoint(point)) break; // 如果是起点，终止
		else
		{
			point = CloseSet[point.ParentIndex];

			if (!IsStartPoint(point))
			{
				PathRes.Add(point);
			}
		}
	}

	for (FPoint item : PathRes)
	{
		DrawDebugPoint(GetWorld(), FVector(item.X * 100, item.Y * 100, 0), 10, FColor::Green, false, 3);
	}
}
