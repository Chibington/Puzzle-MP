// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_M_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize();


private:
	UPROPERTY(meta = (BindWidget))
		class UButton* cancelButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* quitButton;

	UFUNCTION()
		void CancelPressed();
	
	UFUNCTION()
		void QuitPressed();
	
};
