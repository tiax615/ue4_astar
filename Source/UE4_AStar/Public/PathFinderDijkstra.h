// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PathFinderBase.h"
#include "PathFinderDijkstra.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(PathFinder), meta=(BlueprintSpawnableComponent) )
class UE4_ASTAR_API UPathFinderDijkstra : public UPathFinderBase
{
	GENERATED_BODY()

public:
	UPathFinderDijkstra();

	virtual float BaseCost(FPoint p) override;
};
