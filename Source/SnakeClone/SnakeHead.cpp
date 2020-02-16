// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeHead.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "SnakeMovementComponent.h"

// Sets default values
ASnakeHead::ASnakeHead()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(TEXT("SnakeHead"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	StaticMesh->SetCollisionProfileName(TEXT("Pawn"));
	RootComponent = StaticMesh;

	MovementComponent = CreateDefaultSubobject<USnakeMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(RootComponent);
}

// Called when the game starts or when spawned
void ASnakeHead::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASnakeHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASnakeHead::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("MoveUp"), IE_Pressed, this, &ASnakeHead::MoveUp);
	PlayerInputComponent->BindAction(TEXT("MoveDown"), IE_Pressed, this, &ASnakeHead::MoveDown);
	PlayerInputComponent->BindAction(TEXT("MoveLeft"), IE_Pressed, this, &ASnakeHead::MoveLeft);
	PlayerInputComponent->BindAction(TEXT("MoveRight"), IE_Pressed, this, &ASnakeHead::MoveRight);
}

UPawnMovementComponent* ASnakeHead::GetMovementComponent() const
{
	return MovementComponent;
}

void ASnakeHead::MoveUp()
{
	MovementComponent->AddInputVector(FVector(1.f, 0.f, 0.f));
}

void ASnakeHead::MoveDown()
{
	MovementComponent->AddInputVector(FVector(-1.f, 0.f, 0.f));
}

void ASnakeHead::MoveLeft()
{
	MovementComponent->AddInputVector(FVector(0.f, -1.f, 0.f));
}

void ASnakeHead::MoveRight()
{
	MovementComponent->AddInputVector(FVector(0.f, 1.f, 0.f));
}

void ASnakeHead::SetReady()
{
	bIsRespawning = false;
	GetWorld()->GetFirstPlayerController()->Possess(this);
}

void ASnakeHead::Respawn()
{
	if (bIsRespawning)
	{
		return;
	}

	bIsRespawning = true;

	MovementComponent->Reset();
	GetWorld()->GetFirstPlayerController()->UnPossess();

	//Play Death animation
	//For now we just wait for next frame and broadcast respawn signal
	GetWorldTimerManager().SetTimerForNextTick(this, &ASnakeHead::DispatchRespawnEvent);
}

void ASnakeHead::DispatchRespawnEvent()
{
	OnRespawn.Broadcast();
}
