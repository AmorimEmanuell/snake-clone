// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"
#include "Components/InputComponent.h"
#include "SnakeHead.h"

ASnakePawn::ASnakePawn()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("MoveUp"), IE_Pressed, this, &ASnakePawn::SendUpCommand);
	PlayerInputComponent->BindAction(TEXT("MoveDown"), IE_Pressed, this, &ASnakePawn::SendDownCommand);
	PlayerInputComponent->BindAction(TEXT("MoveLeft"), IE_Pressed, this, &ASnakePawn::SendLeftCommand);
	PlayerInputComponent->BindAction(TEXT("MoveRight"), IE_Pressed, this, &ASnakePawn::SendRightCommand);
}

void ASnakePawn::SendUpCommand()
{
	if (ControlledHead)
	{
		ControlledHead->TryChangeDirection(FVector(1.f, 0.f, 0.f));
	}
}

void ASnakePawn::SendDownCommand()
{
	if (ControlledHead)
	{
		ControlledHead->TryChangeDirection(FVector(-1.f, 0.f, 0.f));
	}
}

void ASnakePawn::SendLeftCommand()
{
	if (ControlledHead)
	{
		ControlledHead->TryChangeDirection(FVector(0.f, -1.f, 0.f));
	}
}

void ASnakePawn::SendRightCommand()
{
	if (ControlledHead)
	{
		ControlledHead->TryChangeDirection(FVector(0.f, 1.f, 0.f));
	}
}

void ASnakePawn::SetControlledHead(ASnakeHead* Head)
{
	ControlledHead = Head;
}

void ASnakePawn::RemoveControlledHead()
{
	ControlledHead = nullptr;
}
