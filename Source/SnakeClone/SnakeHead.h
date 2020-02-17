// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakeHead.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSnakeRespawnEvent);

UCLASS()
class SNAKECLONE_API ASnakeHead : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USnakeMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY()
	bool bIsRespawning;

	UPROPERTY()
	AActor* LastBodyPart;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ASnakeBodyPart> SnakeBodyPartBP;

	FSnakeRespawnEvent OnRespawn;

public:
	ASnakeHead();

private:
	void DispatchRespawnEvent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void IncreaseSize();
	void Respawn();
	void SetReady();
};
