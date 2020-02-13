// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelPiece.h"
#include "Collectable.generated.h"

/**
 *
 */
UCLASS()
class SNAKECLONE_API ACollectable : public ALevelPiece
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

public:
	// Sets default values for this actor's properties
	ACollectable();
};
