// Fill out your copyright notice in the Description page of Project Settings.


#include "NCGameMode.h"
#include "NCPlayerController.h"
#include "NCGameState.h"
#include "NCPlayerState.h"
#include "NetworkChatting.h"

ANCGameMode::ANCGameMode()
{
	GameStateClass = ANCGameState::StaticClass();
	PlayerControllerClass = ANCPlayerController::StaticClass();
	PlayerStateClass = ANCPlayerState::StaticClass();
}

APlayerController* ANCGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal,
	const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Begin"));

	APlayerController* NewPlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("End"));
	
	return NewPlayerController; 
	
}

void ANCGameMode::PostLogin(APlayerController* NewPlayer)
{
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Begin"));
	
	Super::PostLogin(NewPlayer);

	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("End"));
}
