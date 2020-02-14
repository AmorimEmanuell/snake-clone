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
	TMap<FString, TSubclassOf<class ALevelPiece>> LevelPiece;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcess = "true"))
	TSubclassOf<class AFloorTile> FloorTile;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcess = "true"))
	TSubclassOf<class ASnake> Player;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcess = "true"))
	float Spacing;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcess = "true"))
	float HeightOffset;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcess = "true"))
	TArray<FString> LevelLayoutInfo;

	TArray<FLevelRowStruct> SpawnedRows;

public:
	// Sets default values for this actor's properties
	ALevelCreator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};

USTRUCT()
struct FLevelRowStruct
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AFloorTile*> Columns;
};
