// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"




void ALobbyGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	++numOfPlayers;

	if (numOfPlayers >= 3)
	{
		UWorld* worldRef = GetWorld();
		if (!ensure(worldRef != nullptr))return;

		bUseSeamlessTravel = true;
		worldRef->ServerTravel("World'/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");
	}
}

void ALobbyGameMode::Logout(AController * Exiting)
{
	Super::Logout(Exiting);
	--numOfPlayers;
}
