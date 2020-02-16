// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelCreator.generated.h"

UCLASS()
class SNAKECLONE_API ALevelCreator : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcess = "true"))
	TMap<FString, TSubclassOf<class ALevelPiece>> LevelPieceBP;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcess = "true"))
	TSubclassOf<class AFloorTile> FloorTileBP;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcess = "true"))
	TSubclassOf<class ASnakeHead> PlayerBP;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcess = "true"))
	float TileSize;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcess = "true"))
	float SpaceBetweenTiles;

	UPROPERTY()
	TArray<FString> LevelLayoutInfo;

	UPROPERTY()
	ASnakeHead* SpawnedPlayer;

	UPROPERTY()
	FVector StartPlayerPosition;

public:
	ALevelCreator();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

private:
	UFUNCTION()
	void RespawnPlayer();
};
