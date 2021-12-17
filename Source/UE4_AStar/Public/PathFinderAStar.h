// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PathFinderBase.h"
#include "PathFinderAStar.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(PathFinder), meta=(BlueprintSpawnableComponent) )
class UE4_ASTAR_API UPathFinderAStar : public UPathFinderBase
{
	GENERATED_BODY()

public:
	UPathFinderAStar();

	virtual float BaseCost(FPoint p) override;
	virtual float HeuristicCost(FPoint p) override;

public:
	// virtual void FindPathStep() override;
};
