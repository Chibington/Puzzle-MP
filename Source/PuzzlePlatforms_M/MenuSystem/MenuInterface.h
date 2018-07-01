// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface //your interface that inherits from the default interface class
{
	GENERATED_BODY() // you do not modify this
};

/**
 * 
 */
class PUZZLEPLATFORMS_M_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Host() = 0; //you need "pure" virtual functions. These are functions in which you EXPECT the children to define and is not defined in the class it is created


	
};
