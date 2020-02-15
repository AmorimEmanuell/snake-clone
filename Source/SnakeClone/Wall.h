// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelPiece.h"
#include "Wall.generated.h"

/**
 * 
 */
UCLASS()
class SNAKECLONE_API AWall : public ALevelPiece
{
	GENERATED_BODY()

private:
	virtual void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor) override;
};
