// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"

// Sets default values
ASnake::ASnake()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(TEXT("SnakeHead"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	StaticMesh->SetCollisionProfileName(TEXT("Pawn"));
	RootComponent = StaticMesh;
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

	if (CurrentDirection.IsZero())
	{
		return;
	}

	if (ElapsedRotationTime < HeadRotationDuration)
	{
		ElapsedRotationTime += DeltaTime;

		float RotationProgress = ElapsedRotationTime / HeadRotationDuration;
		FRotator DesiredRotationThisFrame = FMath::Lerp(HeadStartRotation, HeadEndRotation, RotationProgress);
		SetActorRotation(DesiredRotationThisFrame);
	}

	FHitResult Hit;
	AddActorWorldOffset(CurrentDirection * DeltaTime * Speed, true, &Hit);
	if (Hit.IsValidBlockingHit())
	{
		UE_LOG(LogTemp, Display, TEXT("%s"), *Hit.GetActor()->GetName());
	}
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
	ChangeDirection(FVector(1.f, 0.f, 0.f));
}

void ASnake::MoveDown()
{
	ChangeDirection(FVector(-1.f, 0.f, 0.f));
}

void ASnake::MoveLeft()
{
	ChangeDirection(FVector(0.f, -1.f, 0.f));
}

void ASnake::MoveRight()
{
	ChangeDirection(FVector(0.f, 1.f, 0.f));
}

void ASnake::ChangeDirection(FVector NextDirection)
{
	if (FVector::DotProduct(NextDirection, CurrentDirection) != -1.f)
	{
		CurrentDirection = NextDirection;
		HeadStartRotation = GetActorRotation();
		HeadEndRotation = CurrentDirection.Rotation();
		ElapsedRotationTime = 0;
	}
}

void ASnake::SetReady()
{
	bIsRespawning = false;
	GetWorld()->GetFirstPlayerController()->Possess(this);
}

void ASnake::Respawn()
{
	if (bIsRespawning)
	{
		return;
	}

	bIsRespawning = true;

	//Play Death animation

	CurrentDirection = FVector(0.f);
	GetWorld()->GetFirstPlayerController()->UnPossess();

	//For now we just wait for next frame and broadcast respawn signal
	GetWorldTimerManager().SetTimerForNextTick(this, &ASnake::SendRespawnSignal);
}

void ASnake::SendRespawnSignal()
{
	UE_LOG(LogTemp, Display, TEXT("ASnake::SendRespawnSignal"));
	OnRespawn.Broadcast();
}
