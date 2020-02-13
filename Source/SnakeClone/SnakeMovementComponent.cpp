// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeMovementComponent.h"

void USnakeMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	FVector InputVector = ConsumeInputVector();

	if (LastInputVector != InputVector)
	{
		ElapsedRotationTime = 0.f;
		LastInputVector = InputVector;
		InitialRotation = UpdatedComponent->GetComponentRotation();
	}

	FVector DesiredMovementThisFrame = InputVector.GetClampedToMaxSize(1.f) * DeltaTime * Speed;

	FRotator FinalRotation = InputVector.Rotation();
	float RotationProgress = FMath::Clamp(ElapsedRotationTime / TotalRotationTime, 0.f, 1.f);
	UE_LOG(LogTemp, Display, TEXT("ElapsedRotationTime %f TotalRotationTime %f RotationProgress %f"), ElapsedRotationTime, TotalRotationTime, RotationProgress);
	ElapsedRotationTime += DeltaTime;
	FRotator DesiredRotationThisFrame = FMath::Lerp(InitialRotation, FinalRotation, RotationProgress);

	FHitResult Hit;
	SafeMoveUpdatedComponent(DesiredMovementThisFrame, DesiredRotationThisFrame, true, Hit);
}
