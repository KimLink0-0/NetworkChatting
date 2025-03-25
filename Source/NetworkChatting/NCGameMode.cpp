// Fill out your copyright notice in the Description page of Project Settings.


#include "NCGameMode.h"
#include "NCPlayerController.h"
#include "NCGameState.h"
#include "NCPlayerState.h"

ANCGameMode::ANCGameMode()
{
	GameStateClass = ANCGameState::StaticClass();
	PlayerControllerClass = ANCPlayerController::StaticClass();
	PlayerStateClass = ANCPlayerState::StaticClass();
}

APlayerController* ANCGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal,
	const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	
	APlayerController* NewController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	if (NewController->IsLocalPlayerController())
	{
		NewController->SetName(TEXT("ServerController"));
	}
	else
	{
		
	}
	
	
	return NewController;
}


void ANCGameMode::PostLogin(APlayerController* NewPlayer)
{
	
	Super::PostLogin(NewPlayer);
}
