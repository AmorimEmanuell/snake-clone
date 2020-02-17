// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable_Egg.h"
#include "SnakeHead.h"
#include "Components/StaticMeshComponent.h"

void ACollectable_Egg::OnOverlapBegin(AActor* OverlapedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(TEXT("SnakeHead")))
	{
		UE_LOG(LogTemp, Display, TEXT("ACollectable_Egg::OnOverlapBegin"));

		StaticMesh->SetGenerateOverlapEvents(false);

		ASnakeHead* SnakeHead = Cast<ASnakeHead>(OtherActor);
		SnakeHead->IncreaseSize();

		//Play collecting animation.
		Destroy();
	}
}
