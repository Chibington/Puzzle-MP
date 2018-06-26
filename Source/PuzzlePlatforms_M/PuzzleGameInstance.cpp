// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGameInstance.h"
#include "Engine/Engine.h"


UPuzzleGameInstance::UPuzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor"));
}

void UPuzzleGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Initialized"));
}

void UPuzzleGameInstance::Host()
{
	UEngine* engineRef = GetEngine();
	if (!ensure(engineRef != nullptr) )return;

	engineRef->AddOnScreenDebugMessage(0, 3, FColor::Green, TEXT("Hosting"));

	UWorld* worldRef = GetWorld();
	if (!ensure(worldRef != nullptr))return;

	worldRef->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"); //URL is where the server is sent to. Adding "?listen" makes that the server. 
																															//Allows for other games to connect to it

}

void UPuzzleGameInstance::Join(const FString& address)
{
	UEngine* engineRef = GetEngine();
	if (!ensure(engineRef != nullptr))return;

	engineRef->AddOnScreenDebugMessage(0, 4, FColor::Green, FString::Printf(TEXT("Joining %s"), *address));

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr))return;

	playerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);


}
