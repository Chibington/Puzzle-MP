// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"
#include "Components/Button.h"


bool UInGameMenu::Initialize()
{
	bool success = Super::Initialize();
	if (!success) { return false; }

	if (!ensure(cancelButton != nullptr)) return false;
	cancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelPressed);

	if (!ensure(quitButton != nullptr)) return false;
	quitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitPressed);

	return true;
}

void UInGameMenu::CancelPressed()
{
	TeardownUI();
}

void UInGameMenu::QuitPressed()
{
	if (menuInterface != nullptr)
	{
		TeardownUI();
		menuInterface->LoadMainMenu();
	}
}
