// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "UObject/ConstructorHelpers.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow.WBP_ServerRow_C"));
	if (!ensure(ServerRowBPClass.Class != nullptr))return;

	ServerRowClass = ServerRowBPClass.Class;
}

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

	if (!ensure(quitButton != nullptr)) return false;
	quitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitPressed);

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

void UMainMenu::SetServerList(TArray<FString> serverNames)
{	
	UWorld* world = this->GetWorld();
	if (!ensure(world != nullptr))return;

	serverList->ClearChildren();

	for (const FString& serverName : serverNames)
	{
		UServerRow* row = CreateWidget<UServerRow>(world, ServerRowClass);
		if (!ensure(row != nullptr))return;

		row->serverName->SetText(FText::FromString(serverName));

		serverList->AddChild(row);
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(menuSwitcher != nullptr))return;
	if (!ensure(joinMenu != nullptr))return;
	menuSwitcher->SetActiveWidget(joinMenu);
	if (menuInterface != nullptr)
	{
		menuInterface->RefreshServerList();
	}
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
		/*if (!ensure(IPAddressField != nullptr))return;
		const FString& address = IPAddressField->GetText().ToString();
		menuInterface->Join(address);*/
		
	}
}

void UMainMenu::QuitPressed()
{
	UWorld* world = GetWorld();
	if (!ensure(world != nullptr))return;

	APlayerController* playerController = world->GetFirstPlayerController();
	if (!ensure(playerController != nullptr))return;

	playerController->ConsoleCommand("quit");
}
