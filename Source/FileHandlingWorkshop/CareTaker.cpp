// Fill out your copyright notice in the Description page of Project Settings.

#include "CareTaker.h"
#include "Math/UnrealMathUtility.h"
#include "MementoComponent.h"
#include "Unit.h"

// Sets default values
ACareTaker::ACareTaker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACareTaker::BeginPlay()
{
	Super::BeginPlay();

	names = loadFileData(*NamesFilePath);
	epithets = loadFileData(*EpithetsFilePath);	
	//for (int i = 0; i < 20; i++)
	{
		Spawn();
	}

}

// Called every frame
void ACareTaker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<FString> ACareTaker::loadFileData(FString path)
{
	TArray<FString> FileContent;

	if (FFileHelper::LoadFileToStringArray(FileContent , *path))
	{
		// Successfully read the file contents
		UE_LOG(LogTemp, Warning, TEXT("File Loaded"));
	}
	else
	{
		// Failed to read the file
		UE_LOG(LogTemp, Error, TEXT("Failed to read the file"));
	}

	return FileContent;
}

AUnit* ACareTaker::Spawn() {
	int nameSeed = FMath::RandRange(0, names.Num()-1);
	int epithetSeed = FMath::RandRange(0, epithets.Num()-1);

	FString UnitName;
	if (names.IsValidIndex(nameSeed)) {
		UnitName = names[nameSeed];
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Invalid Name Seed"));
		UnitName = "ERROR";
	}

	if (epithets.IsValidIndex(epithetSeed)) {
		UnitName.Append(", ");
		UnitName.Append(epithets[epithetSeed]);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Invalid Epithet Seed"));
		UnitName = "ERROR";
	}

	AUnit* NewActor = GetWorld()->SpawnActor<AUnit>(AUnit::StaticClass(), GetActorLocation(), GetActorRotation());

	float RandX = FMath::RandRange(-50, 50);
	float RandY = FMath::RandRange(-50, 50);

	NewActor->Initialize(UnitName, FVector(RandX, RandY, 0));

	return NewActor;
}

void ACareTaker::SaveAll() {
	UWorld* world = GetWorld();
	if (world) {
		for (TObjectIterator<AUnit> i; i; ++i) {
			WriteJsonObjectToFile(i->mementoComponent->SaveData());
		}
	}
}

void ACareTaker::LoadAll() {
	FString FilePath = FPaths::ProjectContentDir() + TEXT("YourData.json");
	FString JsonString;
	if (FFileHelper::LoadFileToString(JsonString, *FilePath))
	{
		// Successfully read the file contents

		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			AUnit* NewActor = GetWorld()->SpawnActor<AUnit>(AUnit::StaticClass(), GetActorLocation(), GetActorRotation());
			NewActor->mementoComponent->LoadData(JsonObject);

		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("failure to deserialize data"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("failure to read data"));
	}
}

void ACareTaker::WriteJsonObjectToFile(TSharedPtr<FJsonObject> JsonObject) {
	
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	FString FilePath = FPaths::ProjectContentDir() + TEXT("YourData.json");
	if (FFileHelper::SaveStringToFile(JsonString, *FilePath))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("successfully saved Data"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("failure to save data"));
	}
}
