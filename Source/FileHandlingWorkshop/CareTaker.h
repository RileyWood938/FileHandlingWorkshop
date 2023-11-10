// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "GameFramework/Actor.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"
#include "CareTaker.generated.h"

UCLASS()
class FILEHANDLINGWORKSHOP_API ACareTaker : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACareTaker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FString NamesFilePath;

	UPROPERTY(EditAnywhere)
	FString EpithetsFilePath;

	UFUNCTION(BlueprintCallable)
	class AUnit* Spawn();

	UFUNCTION(BlueprintCallable)
	void SaveAll();

	UFUNCTION(BlueprintCallable)
	void LoadAll();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<FString> loadFileData(FString path);
	TArray<FString> names;
	TArray<FString> epithets;
	void WriteJsonObjectToFile(TSharedPtr<FJsonObject> JsonObject);

};
