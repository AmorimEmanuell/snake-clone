// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AWall::AWall()
{
	StaticMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
}
