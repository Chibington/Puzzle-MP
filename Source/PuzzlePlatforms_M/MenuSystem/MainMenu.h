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


protected:
		virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* host;
	
	UPROPERTY(meta = (BindWidget))
		class UButton* join;

	UFUNCTION()
		void HostServer();

	IMenuInterface* menuInterface;
};
