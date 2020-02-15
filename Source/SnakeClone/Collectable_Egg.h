// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelPiece.h"
#include "Collectable_Egg.generated.h"

/**
 * 
 */
UCLASS()
class SNAKECLONE_API ACollectable_Egg : public ALevelPiece
{
	GENERATED_BODY()
	
protected:
	virtual void OnOverlapBegin(AActor* OverlapedActor, AActor* OtherActor) override;
};
