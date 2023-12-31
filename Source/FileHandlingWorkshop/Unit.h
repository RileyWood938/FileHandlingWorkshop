// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Unit.generated.h"

class UMementoComponent;
UCLASS()
class FILEHANDLINGWORKSHOP_API AUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Initialize(FString name, FVector pos);
	UPROPERTY(VisibleAnywhere)
	UMementoComponent* mementoComponent;

private:
	FString unitName;
};
