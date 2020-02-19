// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeHead.h"
#include "TimerManager.h"
#include "SnakeBody.h"
#include "SnakePawn.h"
#include "SnakeMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"

ASnakeHead::ASnakeHead()
{
	Tags.Add(TEXT("SnakeHead"));
	bIsLastPart = true;
}

void ASnakeHead::BeginPlay()
{
	Super::BeginPlay();

	LastSnakePart = this;
}

FVector ASnakeHead::GetVelocityForThisFrame(float DeltaTime)
{
	return CurrentDirection * MoveSpeed * DeltaTime;
}

void ASnakeHead::TryChangeDirection(FVector ToDirection)
{
	if (FVector::DotProduct(CurrentDirection, ToDirection) == -1.f || IsRotating())
	{
		return;
	}

	if (CurrentDirection != ToDirection)
	{
		AddPositionToHistory(GetActorLocation());

		CurrentDirection = ToDirection;

		ElapsedRotationTime = 0.f;
		StartRotation = GetActorRotation();
	}
}

void ASnakeHead::SetReady()
{
	bIsRespawning = false;
	ASnakePawn* SnakePawn = Cast<ASnakePawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	SnakePawn->SetControlledHead(this);
}

void ASnakeHead::IncreaseSize()
{
	UWorld *World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("ASnakeHead::IncreaseSize(Unable to find world instance)"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	FVector LastPartLocation = LastSnakePart->GetActorLocation();
	FRotator LastPartRotation = LastSnakePart->GetActorRotation();

	ASnakeBody *BodyPart = World->SpawnActor<ASnakeBody>(SnakeBodyBP, LastPartLocation, LastPartRotation, SpawnParams);
	BodyPart->RegisterPartToFollow(LastSnakePart);
	LastSnakePart = BodyPart;
}

void ASnakeHead::Respawn()
{
	if (bIsRespawning)
	{
		return;
	}

	bIsRespawning = true;

	CurrentDirection = FVector(0.f);
	ElapsedRotationTime = RotationTime;
	MoveHistory.Empty();

	ASnakePawn* SnakePawn = Cast<ASnakePawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	SnakePawn->RemoveControlledHead();

	//Play defeat animation
	GetWorldTimerManager().SetTimerForNextTick(this, &ASnakeHead::DispatchRespawnEvent);
}

void ASnakeHead::DispatchRespawnEvent()
{
	OnRespawn.Broadcast();
}
