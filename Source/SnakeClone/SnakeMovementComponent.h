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
	FVector LastInputVector = FVector(0.f);
	FRotator InitialRotation = FRotator(0.f);
	float ElapsedRotationTime = 0.f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TotalRotationTime = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 200.f;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFuntion) override;

private:
	bool InputVectorIsInOppositeDirection(FVector InputVector);
};
