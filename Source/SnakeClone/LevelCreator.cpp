// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelCreator.h"
#include "FloorTile.h"
#include "Snake.h"
#include "Engine/World.h"

// Sets default values
ALevelCreator::ALevelCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LevelLayoutInfo.Add(TEXT("w,w,w,w,w,w,w,w,w,w,w,w,w"));
	LevelLayoutInfo.Add(TEXT("w,_,_,_,_,_,_,_,_,_,_,_,w"));
	LevelLayoutInfo.Add(TEXT("w,_,_,_,_,_,_,_,_,_,_,_,w"));
	LevelLayoutInfo.Add(TEXT("w,_,_,_,_,_,_,_,_,_,_,_,w"));
	LevelLayoutInfo.Add(TEXT("w,_,_,_,_,_,_,_,_,_,_,_,w"));
	LevelLayoutInfo.Add(TEXT("w,_,_,_,_,_,_,_,_,_,_,_,w"));
	LevelLayoutInfo.Add(TEXT("w,_,_,_,_,_,_,_,_,_,_,_,w"));
	LevelLayoutInfo.Add(TEXT("w,_,_,_,_,_,_,_,_,_,_,_,w"));
	LevelLayoutInfo.Add(TEXT("w,s,_,_,_,_,_,_,_,_,_,_,w"));
	LevelLayoutInfo.Add(TEXT("w,w,w,w,w,w,w,w,w,w,w,w,w"));
}

// Called when the game starts or when spawned
void ALevelCreator::BeginPlay()
{
	Super::BeginPlay();

	if (!FloorTileBP)
	{
		UE_LOG(LogTemp, Display, TEXT("FloorTileBlueprint not set"));
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Display, TEXT("World doesn't exist"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	FVector TileLocation = FVector(0.f);
	FRotator TileRotation = FRotator(0.f);

	for (int i = 0; i < LevelLayoutInfo.Num(); i++)
	{
		TileLocation.X = (LevelLayoutInfo.Num() - 1 - i) * TileSize;

		TArray<FString> RowLayoutInfo;
		LevelLayoutInfo[i].ParseIntoArray(RowLayoutInfo, TEXT(","), true);

		for (int j = 0; j < RowLayoutInfo.Num(); j++)
		{
			TileLocation.Y = j * TileSize;

			AFloorTile* SpawnedTile = World->SpawnActor<AFloorTile>(FloorTileBP, TileLocation, TileRotation, SpawnParams);

			FString LayoutInfoChar = RowLayoutInfo[j];
			LayoutInfoChar.TrimStartAndEndInline();
			if (LevelPieceBP.Contains(LayoutInfoChar))
			{
				TSubclassOf<ALevelPiece> PieceToSpawn = LevelPieceBP[LayoutInfoChar];
				World->SpawnActor<ALevelPiece>(PieceToSpawn, TileLocation, TileRotation, SpawnParams);
			}
			else if (LayoutInfoChar.Equals(TEXT("s")))
			{
				StartPlayerPosition = TileLocation;
				SpawnedPlayer = World->SpawnActor<ASnake>(PlayerBP, TileLocation, TileRotation, SpawnParams);
				SpawnedPlayer->OnRespawn.AddDynamic(this, &ALevelCreator::RespawnPlayer);
			}
		}
	}

	SpawnedPlayer->SetReady();
}

void ALevelCreator::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (SpawnedPlayer)
	{
		SpawnedPlayer->OnRespawn.RemoveDynamic(this, &ALevelCreator::RespawnPlayer);
	}
}

void ALevelCreator::RespawnPlayer()
{
	UE_LOG(LogTemp, Display, TEXT("ALevelCreator::RespawnPlayer"));
	//Reset level state
	//Reset player state(size, keys, etc...)
	SpawnedPlayer->SetActorLocationAndRotation(StartPlayerPosition, FRotator(0.f));
	SpawnedPlayer->SetReady();
}
