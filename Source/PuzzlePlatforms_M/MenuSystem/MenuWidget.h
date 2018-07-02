// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_M_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetupUI();
	void TeardownUI();
	
	void SetMenuInterface(IMenuInterface* menuInterface);
	
protected:
	IMenuInterface * menuInterface;
};
