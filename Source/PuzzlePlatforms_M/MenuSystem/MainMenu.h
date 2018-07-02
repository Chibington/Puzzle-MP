// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_M_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface* menuInterface);

	void SetupUI();
	void TeardownUI();

	virtual void OnLevelRemovedFromWorld(ULevel* inLevel, UWorld* inWorld) override;

protected:
		virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* hostButton;
	
	UPROPERTY(meta = (BindWidget))
		class UButton* joinButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* cancelJoinButton;

	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* menuSwitcher;

	UPROPERTY(meta = (BindWidget))
		class UWidget* joinMenu;

	UPROPERTY(meta = (BindWidget))
		class UWidget* mainMenu;

	UFUNCTION()
		void HostServer();

	UFUNCTION()
		void OpenJoinMenu();

	UFUNCTION()
		void OpenMainMenu();

	IMenuInterface* menuInterface;
};
