// Fill out your copyright notice in the Description page of Project Settings.


#include "MementoComponent.h"
#include "Unit.h"

// Sets default values for this component's properties
UMementoComponent::UMementoComponent()
{

}

// Called when the game starts
void UMementoComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

TSharedPtr<FJsonObject> UMementoComponent::SaveData() {
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

    JsonObject->SetStringField(TEXT("Name"), name);

    JsonObject->SetNumberField(TEXT("Position X"), position.X);
	JsonObject->SetNumberField(TEXT("Position Y"), position.Y);
	JsonObject->SetNumberField(TEXT("Position Z"), position.Z);


	return JsonObject;
}

void UMementoComponent::LoadData(TSharedPtr<FJsonObject> JsonObject) 
{
	FString nameValue;
	float posX;
	float posY;
	float posZ;

	if (JsonObject->TryGetStringField(TEXT("Name"), nameValue) 
		&& JsonObject->TryGetNumberField(TEXT("Position X"), posX) 
		&& JsonObject->TryGetNumberField(TEXT("Position Y"), posY) 
		&& JsonObject->TryGetNumberField(TEXT("Position Z"), posZ))
	{
		name = nameValue;
		position = FVector(posX, posY, posZ);
		if (AUnit* owner = Cast<AUnit>(GetOwner()) )
		{
			owner->Initialize(nameValue, position);
		}
	}
}