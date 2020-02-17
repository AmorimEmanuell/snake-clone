// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBodyPart.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASnakeBodyPart::ASnakeBodyPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	StaticMesh->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = StaticMesh;
}

void ASnakeBodyPart::BeginPlay()
{
	Super::BeginPlay();
}

void ASnakeBodyPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!BodyPartToFollow)
	{
		return;
	}
}

void ASnakeBodyPart::SetBodyPartToFollow(AActor* BodyPart)
{
	BodyPartToFollow = BodyPart;
}
