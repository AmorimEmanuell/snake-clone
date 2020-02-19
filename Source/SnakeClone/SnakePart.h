// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelPiece.h"
#include "SnakePart.generated.h"

UCLASS()
class SNAKECLONE_API ASnakePart : public ALevelPiece
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<FVector> MoveHistory;

	UPROPERTY()
	bool bIsLastPart;

	UPROPERTY()
	FVector CurrentDirection;

	float ElapsedRotationTime;

	FRotator StartRotation;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

public:
	ASnakePart();

protected:
	virtual FVector GetVelocityForThisFrame(float DeltaTime);
	virtual FRotator GetRotationForThisFrame(float DeltaTime);

	bool IsRotating();

public:
	virtual void Tick(float DeltaTime) override;

	void AddPositionToHistory(FVector Position);
	FVector GetOldestPosition();
	void RemoveOldestPosition();
	float GetDistanceFromHistory();
	void SetIsLastPart(bool IsLastPart);
};
