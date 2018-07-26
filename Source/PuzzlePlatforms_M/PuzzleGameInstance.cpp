// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"

#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"

const static FName SESSION_NAME = TEXT("Main Session");

UPuzzleGameInstance::UPuzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu.WBP_MainMenu_C")); 
	if (!ensure(MenuBPClass.Class != nullptr))return;

	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu.WBP_InGameMenu_C"));
	if (!ensure(InGameMenuBPClass.Class != nullptr))return;

	InGameMenuClass = InGameMenuBPClass.Class;

	
}

void UPuzzleGameInstance::Init()
{
	IOnlineSubsystem* subsystemRef = IOnlineSubsystem::Get();
	if (subsystemRef != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found subsystem %s"), *subsystemRef->GetSubsystemName().ToString());
		sessionInterface = subsystemRef->GetSessionInterface(); //Shared pointer that counts references
		if (sessionInterface.IsValid()) //IOnlineSessionPtrs are shared pointers.
		{
			UE_LOG(LogTemp, Warning, TEXT("Found session interface"));
			FOnlineSessionSettings sessionSettings;
			sessionInterface->CreateSession(0, TEXT("Main Session"), sessionSettings);

			sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzleGameInstance::OnCreateSessionComplete); //Attaches delegates to the events
			sessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzleGameInstance::OnDestroySessionComplete);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found no OSS"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

void UPuzzleGameInstance::Host()
{
	if (sessionInterface.IsValid())
	{
		auto existingSession = sessionInterface->GetNamedSession(SESSION_NAME); //tries to create server w/ the existing name
		if (existingSession != nullptr)
		{
			sessionInterface->DestroySession(SESSION_NAME); //If the server exits, destroy it. Then, once destroyed it'll go to the delegate 'OnDestroyedSessionComplete' where another will be created
		}
		else
		{
			CreateSession();
		}
	}
}

void UPuzzleGameInstance::CreateSession()
{
	if (sessionInterface.IsValid())
	{
		FOnlineSessionSettings sessionSettings;
		sessionInterface->CreateSession(0, SESSION_NAME, sessionSettings);
	}
}

void UPuzzleGameInstance::OnCreateSessionComplete(FName sessionName, bool success) //Runs asynchronously. Waits for the 'CreateSession' to run fully before it runs
{
	if (!success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not create session"));
		return;
	}
	
	if (menu != nullptr)
	{
		menu->TeardownUI();
	}
		
	UEngine* engineRef = GetEngine();
	if (!ensure(engineRef != nullptr))return;

	engineRef->AddOnScreenDebugMessage(0, 3, FColor::Green, TEXT("Hosting"));

	UWorld* worldRef = GetWorld();
	if (!ensure(worldRef != nullptr))return;

	worldRef->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"); //URL is where the server is sent to. Adding "?listen" makes that the server. 
																					  //Allows for other games to connect to it
}

void UPuzzleGameInstance::OnDestroySessionComplete(FName sessionName, bool success)
{
	if (success)
	{
		CreateSession();
	}
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

void UPuzzleGameInstance::LoadMainMenu()
{
	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr))return;

	playerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute); //Sends a SINGLE client to the address(opens the main menu level which automatically opens the main UI)
}

void UPuzzleGameInstance::TeardownMenu()
{
	if (menu != nullptr)
	{
		menu->TeardownUI();
	}
}


void UPuzzleGameInstance::LoadMenuWidget()
{
	if (!ensure(MenuClass != nullptr))return;

	menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(menu != nullptr))return;

	menu->SetupUI();

	menu->SetMenuInterface(this);

}

void UPuzzleGameInstance::LoadInGameMenu()
{
	if (!ensure(MenuClass != nullptr))return;

	UMenuWidget* menu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (!ensure(menu != nullptr))return;

	menu->SetupUI();

	menu->SetMenuInterface(this);

}