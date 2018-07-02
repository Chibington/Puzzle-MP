// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

bool UMainMenu::Initialize()
{
	bool success = Super::Initialize();
	if (!success) { return false; }

	if (!ensure(hostButton != nullptr)) return false;
	hostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(joinButton != nullptr)) return false;
	joinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(cancelJoinButton != nullptr)) return false;
	cancelJoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* menuInterface)
{
	this->menuInterface = menuInterface;
}

void UMainMenu::SetupUI()
{
	this->AddToViewport();

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr))return;

	APlayerController* playerController = world->GetFirstPlayerController();
	if (!ensure(playerController != nullptr))return;

	FInputModeUIOnly inputDataBase;
	inputDataBase.SetWidgetToFocus(this->TakeWidget());
	inputDataBase.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	playerController->SetInputMode(inputDataBase);
	playerController->bShowMouseCursor = true;
}

void UMainMenu::TeardownUI()
{
	this->RemoveFromViewport();
	
	UWorld* world = GetWorld();
	if (!ensure(world != nullptr))return;

	APlayerController* playerController = world->GetFirstPlayerController();
	if (!ensure(playerController != nullptr))return;

	FInputModeGameOnly inputDataBase;

	playerController->SetInputMode(inputDataBase);
	playerController->bShowMouseCursor = false;

}

void UMainMenu::OnLevelRemovedFromWorld(ULevel * inLevel, UWorld * inWorld)
{
	//In this game, you change the level when you hit "host" or "join"
	//If you were to put the TeardownUI() logic in here,
	//it would run this method as soon as the level is changed.

	//This makes the logic in the game instance that calls teardownUI obsolete
	//Try this some time
}


void UMainMenu::HostServer()
{
	if (menuInterface != nullptr)
	{
		menuInterface->Host();
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(menuSwitcher != nullptr))return;
	if (!ensure(joinMenu != nullptr))return;
	menuSwitcher->SetActiveWidget(joinMenu);

}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(menuSwitcher != nullptr))return;
	if (!ensure(mainMenu != nullptr))return;
	menuSwitcher->SetActiveWidget(mainMenu);
}
