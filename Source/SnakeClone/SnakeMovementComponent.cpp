// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeMovementComponent.h"

USnakeMovementComponent::USnakeMovementComponent()
{
	CurrentInputVector = FVector(0.f);
	StartHeadRotation = FRotator(0.f);
	TotalRotationTime = 0.5f;
	ElapsedRotationTime = TotalRotationTime;
	Speed = 200.f;
}

void USnakeMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	ValidateInputVector(ConsumeInputVector());
	FVector VelocityThisFrame = CurrentInputVector * DeltaTime * Speed;
	FRotator RotationThisFrame = GetRotationForThisFrame(DeltaTime);

	FHitResult Hit;
	SafeMoveUpdatedComponent(VelocityThisFrame, RotationThisFrame, true, Hit);
}

void USnakeMovementComponent::Reset()
{
	CurrentInputVector = FVector(0.f);
	ElapsedRotationTime = TotalRotationTime;
}

FRotator USnakeMovementComponent::GetRotationForThisFrame(float DeltaTime)
{
	if (!IsRotating())
	{
		return UpdatedComponent->GetComponentRotation();
	}

	ElapsedRotationTime += DeltaTime;
	float RotationProgress = ElapsedRotationTime / TotalRotationTime;

	return FMath::Lerp(StartHeadRotation, CurrentInputVector.Rotation(), RotationProgress);
}

void USnakeMovementComponent::ValidateInputVector(FVector InputVector)
{
	if (InputVectorIsInOppositeDirection(InputVector) || InputVector.IsZero() || IsRotating())
	{
		return;
	}

	if (InputVector != CurrentInputVector)
	{
		CurrentInputVector = InputVector;

		//To rotate head
		ElapsedRotationTime = 0.f;
		StartHeadRotation = UpdatedComponent->GetComponentRotation();
	}
}

bool USnakeMovementComponent::InputVectorIsInOppositeDirection(FVector InputVector)
{
	return FVector::DotProduct(InputVector, CurrentInputVector) == -1.f;
}

bool USnakeMovementComponent::IsRotating()
{
	return ElapsedRotationTime < TotalRotationTime;
}
