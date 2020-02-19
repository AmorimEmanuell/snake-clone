// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelPiece.h"
#include "Components/StaticMeshComponent.h"

ALevelPiece::ALevelPiece()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = StaticMesh;
}

void ALevelPiece::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ALevelPiece::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ALevelPiece::OnOverlapEnd);
}

void ALevelPiece::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnActorBeginOverlap.RemoveDynamic(this, &ALevelPiece::OnOverlapBegin);
	OnActorEndOverlap.RemoveDynamic(this, &ALevelPiece::OnOverlapEnd);
}

void ALevelPiece::OnOverlapBegin(AActor *OverlappedActor, AActor *OtherActor)
{
}

void ALevelPiece::OnOverlapEnd(AActor *OverlappedActor, AActor *OtherActor)
{
}
