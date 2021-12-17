// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PathFinderBase.generated.h"

USTRUCT()
struct FPoint
{
	GENERATED_BODY()

	int X = 0;
	int Y = 0;
	float Cost = 0; // 花费，越高表示代价越大
	int ParentIndex = -1; // 父节点在CloseSet中的索引，即指向上一个点
};

UCLASS( ClassGroup=(PathFinder), meta=(BlueprintSpawnableComponent) )
class UE4_ASTAR_API UPathFinderBase : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPathFinderBase();

	TArray<FString> MapInfoArray; // 地图信息，用于判断哪些格子是不能穿越的障碍物
	FTimerHandle PathFinderTimerHandle; // 定时器句柄，用于FindPathOnce的时候逐次进行寻路
	TArray<FPoint> PathRes; // 最终路径
	bool bFinding; // 是否在进行寻路算法

	TArray<FPoint> OpenSet; // 将要进行分析的点
	TArray<FPoint> CloseSet; // 已经分析完的点
	int RowCurrent; // 起点行
	int ColCurrent; // 起点列
	int RowTarget; // 终点行
	int ColTarget; // 终点列

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 逐次进行寻路算法FindPathStep()，每次间隔是deltaTime秒
	UFUNCTION(BlueprintCallable)
	virtual void FindPathOnce(int rowCurrent, int colCurrent, int rowTarget, int colTarget, float deltaTime);

	// 进行寻路算法，一次执行完FindPathStep()
	UFUNCTION(BlueprintCallable)
	virtual void FindPath(int rowCurrent, int colCurrent, int rowTarget, int colTarget);

	// 开始进行寻路算法，将起点加入OpenSet
	virtual void FindPathStart(int rowCurrent, int colCurrent, int rowTarget, int colTarget);

	// 寻路算法每次执行的内容
	virtual void FindPathStep();
	
	virtual float BaseCost(FPoint p); // 距离起点的移动代价
	virtual float HeuristicCost(FPoint p); // 距离终点的启发函数
	virtual float Cost(FPoint p); // 最终代价

	bool IsValidPoint(int x, int y); // 判断点是否有效
	bool IsInPointList(FPoint p, TArray<FPoint> pointArray); // 判断点是否在某点集中
	bool IsInOpenList(FPoint p); // 点是否在OpenSet
	bool IsInCloseList(FPoint p); // 点是否在CloseSet
	bool IsStartPoint(FPoint p); // 点是否是起点
	bool IsEndPoint(FPoint p); // 点是否是终点
	virtual int SelectPointInOpenList(); // 从OpenSet中选择一个点
	virtual void ProcessPoint(int x, int y, int parentIndex); // 对一个点进行处理
	virtual void BuildPath(FPoint p); // 构建路径
};
