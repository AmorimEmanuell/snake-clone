// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakePawn.generated.h"

UCLASS()
class SNAKECLONE_API ASnakePawn : public APawn
{
	GENERATED_BODY()

private:
	class ASnakeHead* ControlledHead;

public:
	ASnakePawn();

private:
	void SendUpCommand();
	void SendDownCommand();
	void SendLeftCommand();
	void SendRightCommand();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetControlledHead(class ASnakeHead* Head);
	void RemoveControlledHead();
};
