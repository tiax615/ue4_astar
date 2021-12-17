// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PathFinderBase.h"
#include "PathFinderGreedy.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(PathFinder), meta=(BlueprintSpawnableComponent) )
class UE4_ASTAR_API UPathFinderGreedy : public UPathFinderBase
{
	GENERATED_BODY()

public:
	UPathFinderGreedy();

	virtual float HeuristicCost(FPoint p) override;
};
