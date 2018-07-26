// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"

#include "Components/Button.h"
#include "MainMenu.h"

void UServerRow::Setup(UMainMenu * inParent, uint32 inIndex)
{
	parent = inParent;
	index = inIndex;
	rowButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
}

void UServerRow::OnClicked()
{
	parent->SelectIndex(index);
}
