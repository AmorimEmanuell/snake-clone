// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePart.h"

ASnakePart::ASnakePart()
{
	bIsLastPart = false;
	RotationTime = 0.5f;
	ElapsedRotationTime = RotationTime;
	MoveSpeed = 200.f;
}

void ASnakePart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector VelocityThisFrame = GetVelocityForThisFrame(DeltaTime);
	FRotator RotationThisFrame = GetRotationForThisFrame(DeltaTime);

	AddActorWorldOffset(VelocityThisFrame);
	SetActorRotation(RotationThisFrame);
}

FVector ASnakePart::GetVelocityForThisFrame(float DeltaTime)
{
	return FVector();
}

FRotator ASnakePart::GetRotationForThisFrame(float DeltaTime)
{
	if (!IsRotating())
	{
		return GetActorRotation();
	}

	ElapsedRotationTime += DeltaTime;
	float RotationProgress = FMath::Clamp(ElapsedRotationTime / RotationTime, 0.f, 1.f);

	return FMath::Lerp(StartRotation, CurrentDirection.Rotation(), RotationProgress);
}

bool ASnakePart::IsRotating()
{
	return ElapsedRotationTime < RotationTime;
}

void ASnakePart::AddPositionToHistory(FVector Position)
{
	if (!bIsLastPart)
	{
		MoveHistory.Add(Position);
	}
}

FVector ASnakePart::GetOldestPosition()
{
	if (MoveHistory.Num() > 0)
	{
		return MoveHistory[0];
	}

	return GetActorLocation();
}

void ASnakePart::RemoveOldestPosition()
{
	if (MoveHistory.Num() > 0)
	{
		MoveHistory.RemoveAt(0);
	}
}

float ASnakePart::GetDistanceFromHistory()
{
	FVector CurrentLocation = GetActorLocation();
	float TotalDistance = 0.f;
	for (int i = MoveHistory.Num() - 1; i >= 0; i--)
	{
		TotalDistance += FVector::Distance(CurrentLocation, MoveHistory[i]);
		CurrentLocation = MoveHistory[i];
	}

	return TotalDistance;
}

void ASnakePart::SetIsLastPart(bool IsLastPart)
{
	bIsLastPart = IsLastPart;
}
