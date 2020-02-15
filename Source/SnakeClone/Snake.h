// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Snake.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSnakeRespawnEvent);

UCLASS()
class SNAKECLONE_API ASnake : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY()
	FVector CurrentDirection = FVector(0.f);

	UPROPERTY()
	FRotator HeadStartRotation;

	UPROPERTY()
	FRotator HeadEndRotation;

	UPROPERTY()
	float ElapsedRotationTime;

	UPROPERTY()
	bool bIsRespawning;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HeadRotationDuration = .5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 200.f;

	FSnakeRespawnEvent OnRespawn;

public:
	// Sets default values for this pawn's properties
	ASnake();

private:
	void ChangeDirection(FVector InputVector);
	void SendRespawnSignal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Respawn();
	void SetReady();
};
