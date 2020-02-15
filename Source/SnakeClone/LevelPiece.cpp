// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelPiece.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ALevelPiece::ALevelPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = StaticMesh;

	OnActorBeginOverlap.AddDynamic(this, &ALevelPiece::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ALevelPiece::OnOverlapEnd);
}

ALevelPiece::~ALevelPiece()
{
	OnActorBeginOverlap.RemoveDynamic(this, &ALevelPiece::OnOverlapBegin);
	OnActorEndOverlap.RemoveDynamic(this, &ALevelPiece::OnOverlapEnd);
}

void ALevelPiece::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
}

void ALevelPiece::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
}
