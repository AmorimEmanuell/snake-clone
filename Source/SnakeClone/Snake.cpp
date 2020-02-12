// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SnakeMovementComponent.h"

// Sets default values
ASnake::ASnake()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(TEXT("SnakeHead"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	StaticMesh->SetCollisionProfileName(TEXT("Pawn"));
	RootComponent = StaticMesh;

	MovementComponent = CreateDefaultSubobject<USnakeMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
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

	if (MovementComponent)
	{
		MovementComponent->AddInputVector(MovementDirection);
	}
}

UPawnMovementComponent* ASnake::GetMovementComponent() const
{
	return MovementComponent;
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
	MovementDirection = FVector(1.f, 0.f, 0.f);
}

void ASnake::MoveDown()
{
	MovementDirection = FVector(-1.f, 0.f, 0.f);
}

void ASnake::MoveLeft()
{
	MovementDirection = FVector(0.f, -1.f, 0.f);
}

void ASnake::MoveRight()
{
	MovementDirection = FVector(0.f, 1.f, 0.f);
}
