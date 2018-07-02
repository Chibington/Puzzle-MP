// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_M_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
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
		class UButton* joinIPButton;

	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* menuSwitcher;

	UPROPERTY(meta = (BindWidget))
		class UWidget* joinMenu;

	UPROPERTY(meta = (BindWidget))
		class UWidget* mainMenu;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* IPAddressField;

	UFUNCTION()
		void HostServer();

	UFUNCTION()
		void OpenJoinMenu();

	UFUNCTION()
		void OpenMainMenu();

	UFUNCTION()
		void JoinServer();

};
