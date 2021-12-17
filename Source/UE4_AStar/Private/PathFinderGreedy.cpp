// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFinderGreedy.h"

UPathFinderGreedy::UPathFinderGreedy()
{
	ComponentTags.Add("Greedy");
}

float UPathFinderGreedy::HeuristicCost(FPoint p)
{
	return abs(p.X - RowTarget) + abs(p.Y - ColTarget);
}
