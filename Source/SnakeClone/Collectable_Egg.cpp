// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable_Egg.h"

void ACollectable_Egg::OnOverlapBegin(AActor* OverlapedActor, AActor* OtherActor)
{
    if (OtherActor->ActorHasTag(TEXT("SnakeHead")))
    {
        UE_LOG(LogTemp, Display, TEXT("OnOverlapBegin: Egg"));
        //Disable any collision.
        //Increase the Snake size.
        //Play collecting animation.
    }
}
