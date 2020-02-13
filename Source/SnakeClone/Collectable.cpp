// Fill out your copyright notice in the Description page of Project Settings.

#include "Collectable.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACollectable::ACollectable()
{
	StaticMesh->SetCollisionProfileName(TEXT("Trigger"));
	OnActorBeginOverlap.AddDynamic(this, &ACollectable::OnOverlapBegin);
}

void ACollectable::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
}
