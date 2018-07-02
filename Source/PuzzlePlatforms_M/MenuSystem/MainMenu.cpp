// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"


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

	if (!ensure(joinIPButton != nullptr)) return false;
	joinIPButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	return true;
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

void UMainMenu::JoinServer()
{	
	if (menuInterface != nullptr)
	{
		if (!ensure(IPAddressField != nullptr))return;
		const FString& address = IPAddressField->GetText().ToString();
		menuInterface->Join(address);
	}
}
