// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h" //must be added since session interface is a shared pointer(cant be forward declared)

#include "PuzzleGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_M_API UPuzzleGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	UPuzzleGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init();

	UFUNCTION(BlueprintCallable)
		void LoadMenuWidget();

	UFUNCTION(BlueprintCallable)
		void LoadInGameMenu();

	virtual void LoadMainMenu() override;

	virtual void RefreshServerList() override;
	
private:
	UFUNCTION(Exec)
		void Host();

	UFUNCTION(Exec)
		void Join(const FString& address);

		

	void TeardownMenu();

	TSubclassOf<class UUserWidget> MenuClass;

	TSubclassOf<class UUserWidget> InGameMenuClass;
	
	class UMainMenu* menu;

	IOnlineSessionPtr sessionInterface;
	TSharedPtr<class FOnlineSessionSearch> sessionSearch;

	void OnCreateSessionComplete(FName sessionName, bool success);
	void OnDestroySessionComplete(FName sessionName, bool success);
	void OnFindSessionComplete(bool success);

	void CreateSession();
};
