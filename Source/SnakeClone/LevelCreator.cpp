// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelCreator.h"
#include "FloorTile.h"
#include "Engine/World.h"

// Sets default values
ALevelCreator::ALevelCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LevelLayoutInfo.Add(TEXT("w, w, w, w, w, w"));
	LevelLayoutInfo.Add(TEXT("w, _, _, _, _, w"));
	LevelLayoutInfo.Add(TEXT("w, _, _, _, _, w"));
	LevelLayoutInfo.Add(TEXT("w, _, _, _, _, w"));
	LevelLayoutInfo.Add(TEXT("w, s, _, _, _, w"));
	LevelLayoutInfo.Add(TEXT("w, w, w, w, w, w"));
}

// Called when the game starts or when spawned
void ALevelCreator::BeginPlay()
{
	Super::BeginPlay();

	if (!FloorTile)
	{
		UE_LOG(LogTemp, Display, TEXT("FloorTile not set in the Details panel"));
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Display, TEXT("World doesn't exist"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector TileLocation = FVector(0.f);
	FRotator TileRotation = FRotator(0.f);

	for (int i = 0; i < LevelLayoutInfo.Num(); i++)
	{
		SpawnedRows.Add(FLevelRowStruct());

		FString line = LevelLayoutInfo[i];
		TArray<FString> TileInfo;
		line.ParseIntoArray(TileInfo, TEXT(","), true);

		TileLocation.X = (LevelLayoutInfo.Num() - 1 - i) * Spacing;

		for (int j = 0; j < TileInfo.Num(); j++)
		{
			TileLocation.Y = j * Spacing;
			AFloorTile* SpawnedTile = World->SpawnActor<AFloorTile>(FloorTile, TileLocation, TileRotation, SpawnParams);
			SpawnedRows[i].Columns.Add(SpawnedTile);
		}
	}
}
