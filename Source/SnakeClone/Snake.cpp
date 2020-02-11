// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake.h"
#include "Components/InputComponent.h"

// Sets default values
ASnake::ASnake()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASnake::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASnake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentLocation = GetActorLocation();
	currentLocation += currentVelocity;
	SetActorLocation(currentLocation);
}

// Called to bind functionality to input
void ASnake::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("MoveUp"), IE_Pressed, this, &ASnake::MoveUp);
	PlayerInputComponent->BindAction(TEXT("MoveDown"), IE_Pressed, this, &ASnake::MoveDown);
	PlayerInputComponent->BindAction(TEXT("MoveLeft"), IE_Pressed, this, &ASnake::MoveLeft);
	PlayerInputComponent->BindAction(TEXT("MoveRight"), IE_Pressed, this, &ASnake::MoveRight);
}

void ASnake::MoveUp()
{
	UE_LOG(LogTemp, Display, TEXT("MoveUp"));
	currentVelocity = FVector(1.f, 0.f, 0.f);
}

void ASnake::MoveDown()
{
	UE_LOG(LogTemp, Display, TEXT("MoveDown"));
	currentVelocity = FVector(-1.f, 0.f, 0.f);
}

void ASnake::MoveLeft()
{
	UE_LOG(LogTemp, Display, TEXT("MoveLeft"));
	currentVelocity = FVector(0.f, -1.f, 0.f);
}

void ASnake::MoveRight()
{
	UE_LOG(LogTemp, Display, TEXT("MoveRight"));
	currentVelocity = FVector(0.f, 1.f, 0.f);
}
