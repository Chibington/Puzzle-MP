// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"


void UMenuWidget::SetMenuInterface(IMenuInterface* menuInterface)
{
	this->menuInterface = menuInterface;
}

void UMenuWidget::SetupUI()
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

void UMenuWidget::TeardownUI()
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