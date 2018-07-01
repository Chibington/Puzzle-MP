// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"

bool UMainMenu::Initialize()
{
	bool success = Super::Initialize();
	if (!success) { return false; }

	if (!ensure(host != nullptr)) return false;
	host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* menuInterface)
{
	this->menuInterface = menuInterface;
}


void UMainMenu::HostServer()
{
	if (menuInterface != nullptr)
	{
		menuInterface->Host();
	}
}
