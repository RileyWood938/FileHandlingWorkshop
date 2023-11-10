// Fill out your copyright notice in the Description page of Project Settings.

#include "Unit.h"
#include "MementoComponent.h"
#include <Components/SphereComponent.h>


// Sets default values
AUnit::AUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	unitName = "null";

	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// Set default values for the sphere component (optional)
	SphereComponent->InitSphereRadius(50.0f); // Set the initial radius (adjust as needed)
	SphereComponent->bHiddenInGame = false;
	mementoComponent = CreateDefaultSubobject<UMementoComponent>(TEXT("memoryComponent"));

}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnit::Initialize(FString name, FVector pos)
{
	SetActorLocation(pos);
	unitName = name;
	//mementoComponent = CreateDefaultSubobject<UMementoComponent>(TEXT("memoryComponent"));
	//mementoComponent = NewObject<UMementoComponent>(this);
	mementoComponent->position = pos;
	mementoComponent->name = name;
}

