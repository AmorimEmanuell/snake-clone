// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "Components/StaticMeshComponent.h"
#include "SnakeHead.h"

void AWall::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(TEXT("SnakeHead")))
	{
		ASnakeHead* Player = Cast<ASnakeHead>(OtherActor);
		Player->Respawn();
	}
}
