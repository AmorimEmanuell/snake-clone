// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBody.h"
#include "Components/StaticMeshComponent.h"

FVector ASnakeBody::GetVelocityForThisFrame(float DeltaTime)
{
	if (!SnakePartToFollow)
	{
		return FVector(0.f);
	}

	FVector CurrentPosition = GetActorLocation();

	FVector NextPosition = SnakePartToFollow->GetOldestPosition();
	float DistanceToNextPosition = FVector::Distance(NextPosition, CurrentPosition);
	float DistanceFromHistory = SnakePartToFollow->GetDistanceFromHistory();
	float TotalDistanceToSnakePart = DistanceToNextPosition + DistanceFromHistory;

	if (TotalDistanceToSnakePart <= FollowDistance)
	{
		return FVector(0.f);
	}

	FVector NextDirection = NextPosition - CurrentPosition;
	FVector NextDirectionNorm = NextDirection.GetClampedToMaxSize(1.f);

	if (CurrentDirection != NextDirectionNorm)
	{
		CurrentDirection = NextDirectionNorm;

		ElapsedRotationTime = 0.f;
		StartRotation = GetActorRotation();
	}

	FVector VelocityThisFrame = CurrentDirection * MoveSpeed * DeltaTime;

	if (VelocityThisFrame.Size() >= DistanceToNextPosition)
	{
		FVector RemainingVelocity = VelocityThisFrame - NextDirection;

		SnakePartToFollow->RemoveOldestPosition();
		FVector OneStepAheadPosition = SnakePartToFollow->GetOldestPosition();
		FVector OneStepAheadDirection = (OneStepAheadPosition - NextPosition).GetClampedToMaxSize(1.f);
		float RemainingMovementDistance = VelocityThisFrame.Size() - DistanceToNextPosition;

		VelocityThisFrame = CurrentDirection;
		VelocityThisFrame += OneStepAheadDirection * RemainingMovementDistance;

		AddPositionToHistory(NextPosition);
	}

	return VelocityThisFrame;
}

void ASnakeBody::RegisterPartToFollow(ASnakePart* SnakePart)
{
	SnakePartToFollow = SnakePart;
	SnakePart->SetIsLastPart(false);
}
