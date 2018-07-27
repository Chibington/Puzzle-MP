// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_M_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* serverName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* hostUser;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* connectionFraction;
	
	void Setup(class UMainMenu* inParent, uint32 inIndex);

	UPROPERTY(BlueprintReadOnly)
		bool selected = false;

private:
	UPROPERTY()
		class UMainMenu* parent;

	uint32 index;

	UPROPERTY(meta = (BindWidget))
		class UButton* rowButton;
		
	UFUNCTION()
		void OnClicked();

};
