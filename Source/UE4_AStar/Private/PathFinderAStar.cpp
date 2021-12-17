// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFinderAStar.h"

UPathFinderAStar::UPathFinderAStar()
{
	ComponentTags.Add("AStar");
}

float UPathFinderAStar::BaseCost(FPoint p)
{
	return abs(p.X - RowCurrent) + abs(p.Y - ColCurrent);
}

float UPathFinderAStar::HeuristicCost(FPoint p)
{
	return abs(p.X - RowTarget) + abs(p.Y - ColTarget);
}