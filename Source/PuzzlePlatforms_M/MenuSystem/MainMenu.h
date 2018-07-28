// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

USTRUCT()
struct FServerData
{
	GENERATED_BODY();

	FString name;
	uint16 currentPlayers;
	uint16 maxPlayers;
	FString hostUsername;
};

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_M_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:

	UMainMenu(const FObjectInitializer& ObjectInitializer);

	virtual void OnLevelRemovedFromWorld(ULevel* inLevel, UWorld* inWorld) override;

	void SetServerList(TArray<FServerData> serverNames);

	void SelectIndex(uint32 index);
	
protected:
		virtual bool Initialize() override;

private:
	TSubclassOf<class UUserWidget> ServerRowClass;

	UPROPERTY(meta = (BindWidget))
		class UButton* hostButton;
	
	UPROPERTY(meta = (BindWidget))
		class UButton* joinButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* cancelJoinButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* joinIPButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* quitButton;

	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* menuSwitcher;

	UPROPERTY(meta = (BindWidget))
		class UWidget* joinMenu;

	UPROPERTY(meta = (BindWidget))
		class UWidget* mainMenu;

	UPROPERTY(meta = (BindWidget))
		class UWidget* hostMenu;

	UPROPERTY(meta = (BindWidget))
		class UPanelWidget* serverList;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* serverHostName;

	UPROPERTY(meta = (BindWidget))
		class UButton* confirmHostMenuButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* cancelHostMenuButton;

	UFUNCTION()
		void HostServer();

	UFUNCTION()
		void OpenJoinMenu();

	UFUNCTION()
		void OpenMainMenu();

	UFUNCTION()
		void OpenHostMenu();

	UFUNCTION()
		void JoinServer();

	UFUNCTION()
		void QuitPressed();

	TOptional<uint32> selectedIndex;

	void UpdateChildren();

};
