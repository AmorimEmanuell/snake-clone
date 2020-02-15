// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "Components/StaticMeshComponent.h"
#include "Snake.h"

void AWall::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor->ActorHasTag(TEXT("SnakeHead")))
    {
        UE_LOG(LogTemp, Display, TEXT("Wall::OnOverlapBegin"));
        ASnake* Player = Cast<ASnake>(OtherActor);
        Player->Respawn();
    }
}
