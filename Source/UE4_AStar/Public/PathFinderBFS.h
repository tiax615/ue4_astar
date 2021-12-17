// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PathFinderBase.h"
#include "PathFinderBFS.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(PathFinder), meta=(BlueprintSpawnableComponent) )
class UE4_ASTAR_API UPathFinderBFS : public UPathFinderBase
{
	GENERATED_BODY()

public:
	UPathFinderBFS();

	virtual int SelectPointInOpenList() override;
};
