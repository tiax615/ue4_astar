// Fill out your copyright notice in the Description page of Project Settings.


#include "MapCreator.h"

#include "Editor.h"
#include "EditorModeManager.h"
#include "LevelEditorViewport.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Prop.h"

// Sets default values
AMapCreator::AMapCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapCreator::BeginPlay()
{
	Super::BeginPlay();

	LoadMapInfo();
}

// Called every frame
void AMapCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapCreator::LoadMapInfo()
{
	FString path = FPaths::ProjectDir() + "MapInfo.txt";
	FFileHelper::LoadFileToStringArray(MapInfoArray, *path);
}


void AMapCreator::CreateMap()
{
	LoadMapInfo();
	
	if (MapInfoArray.Num() > 0 && GEditor)
	{
		UWorld* world = GEditor->GetLevelViewportClients()[0]->GetWorld();
		ULevel* level = world->GetLevel(0);
		
		for (int i = 0; i < MapInfoArray.Num(); i++)
		{
			if (MapInfoArray[i] == "20") continue; // 道路不生成物体

			// Calc prop's transform
			int row = floor(i / 75);
			int col = i % 75;
			FVector location = FVector(row * 100, col * 100, 0);
			FTransform transform(FRotator::ZeroRotator, location, FVector::OneVector);

			AActor* prop = GEditor->AddActor(level, AProp::StaticClass(), transform);
			prop->SetActorLabel(FString::Printf(TEXT("%s-%d-%d"), *MapInfoArray[i], row, col));
			prop->Tags.Add(*MapInfoArray[i]);

			prop->RegisterAllComponents();
			prop->RerunConstructionScripts();
		}

		GEditor->EditorUpdateComponents();
		world->UpdateWorldComponents(true, false);
		GLevelEditorModeTools().MapChangeNotify();
	}
}


