// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"
#include "TimerManager.h"

#include "PuzzleGameInstance.h"


void ALobbyGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	++numOfPlayers;

	if (numOfPlayers >= 2)
	{
		GetWorldTimerManager().SetTimer(gameStartTimer, this, &ALobbyGameMode::StartGame, 10); //After five seconds, the game will be called.
	
	}
}

void ALobbyGameMode::Logout(AController * Exiting)
{
	Super::Logout(Exiting);
	--numOfPlayers;
}

void ALobbyGameMode::StartGame()
{
	auto gameInstanceRef = Cast<UPuzzleGameInstance>(GetGameInstance());

	if (gameInstanceRef == nullptr)
		return;

	gameInstanceRef->StartSession();

	UWorld* worldRef = GetWorld();
	if (!ensure(worldRef != nullptr))return;

	bUseSeamlessTravel = true;
	worldRef->ServerTravel("World'/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}