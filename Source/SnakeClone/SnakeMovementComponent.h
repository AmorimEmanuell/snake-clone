// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "SnakeMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class SNAKECLONE_API USnakeMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

private:
	FVector CurrentInputVector;
	FRotator StartHeadRotation;
	float ElapsedRotationTime;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TotalRotationTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

public:
	USnakeMovementComponent();

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFuntion) override;

	void Reset();

private:
	FRotator GetRotationForThisFrame(float DeltaTime);
	void ValidateInputVector(FVector InputVector);
	bool InputVectorIsInOppositeDirection(FVector InputVector);
	bool IsRotating();
};
