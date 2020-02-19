// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakePart.h"
#include "SnakeBody.generated.h"

UCLASS()
class SNAKECLONE_API ASnakeBody : public ASnakePart
{
	GENERATED_BODY()

private:
	UPROPERTY()
	ASnakePart *SnakePartToFollow;

	const float FollowDistance = 100.f;

protected:
	virtual FVector GetVelocityForThisFrame(float DeltaTime) override;

public:
	void RegisterPartToFollow(ASnakePart *SnakePart);
};
