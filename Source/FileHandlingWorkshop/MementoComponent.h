// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"
#include "MementoComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FILEHANDLINGWORKSHOP_API UMementoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMementoComponent();

protected:
	virtual void BeginPlay() override;

public:	
	TSharedPtr<FJsonObject> SaveData();
	void LoadData(TSharedPtr<FJsonObject> JsonObject);
	FVector position;
	FString name;
		
};
