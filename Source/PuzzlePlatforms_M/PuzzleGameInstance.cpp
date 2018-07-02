// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"

UPuzzleGameInstance::UPuzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu.WBP_MainMenu_C")); 
	if (!ensure(MenuBPClass.Class != nullptr))return;

	MenuClass = MenuBPClass.Class;

	
}

void UPuzzleGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

void UPuzzleGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr))return;
	
	menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(menu != nullptr))return;

	menu->SetupUI();

	menu->SetMenuInterface(this);

}

void UPuzzleGameInstance::Host()
{
	TeardownMenu();

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
	TeardownMenu();

	UEngine* engineRef = GetEngine();
	if (!ensure(engineRef != nullptr))return;

	engineRef->AddOnScreenDebugMessage(0, 4, FColor::Green, FString::Printf(TEXT("Joining %s"), *address));

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr))return;

	playerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);
}

void UPuzzleGameInstance::TeardownMenu()
{
	if (menu != nullptr)
	{
		menu->TeardownUI();
	}
}
