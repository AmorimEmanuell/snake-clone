// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakePart.h"
#include "SnakeHead.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSnakeHeadOnRespawn);

UCLASS()
class SNAKECLONE_API ASnakeHead : public ASnakePart
{
	GENERATED_BODY()

private:
	UPROPERTY()
	bool bIsRespawning;

	UPROPERTY()
	class ASnakePart *LastSnakePart;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ASnakeBody> SnakeBodyBP;

	FSnakeHeadOnRespawn OnRespawn;

public:
	ASnakeHead();

private:
	void DispatchRespawnEvent();

protected:
	virtual void BeginPlay() override;
	virtual FVector GetVelocityForThisFrame(float DeltaTime) override;

public:
	void TryChangeDirection(FVector ToDirection);

	void IncreaseSize();
	void Respawn();
	void SetReady();
};
