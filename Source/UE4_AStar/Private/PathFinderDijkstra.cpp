// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFinderDijkstra.h"

UPathFinderDijkstra::UPathFinderDijkstra()
{
	ComponentTags.Add("Dijkstra");
}

float UPathFinderDijkstra::BaseCost(FPoint p)
{
	return abs(p.X - RowCurrent) + abs(p.Y - ColCurrent);
}
