// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTile.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFloorTile::AFloorTile()
{
	StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));
}