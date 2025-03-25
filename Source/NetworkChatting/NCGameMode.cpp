// Fill out your copyright notice in the Description page of Project Settings.


#include "NCGameMode.h"
#include "NCPlayerController.h"
#include "NCGameState.h"
#include "NCPlayerState.h"
#include "NetworkChatting.h"
#include "NCHUD.h"

ANCGameMode::ANCGameMode()
{
	GameStateClass = ANCGameState::StaticClass();
	PlayerControllerClass = ANCPlayerController::StaticClass();
	PlayerStateClass = ANCPlayerState::StaticClass();
	HUDClass = ANCHUD::StaticClass();
}

void ANCGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	FString& ErrorMessage)
{
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Begin"))
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("==============================  Connected Client  =============================="));
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("================  Replication Preparation Started On the Server  ================"));
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("End"))
}

APlayerController* ANCGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal,
                                      const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Begin"));

	APlayerController* NewPlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	NC_LOG(LogNetworkC, Log, TEXT("NewController:%s"), *NewPlayerController->GetName());

	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("End"));
	
	return NewPlayerController; 
	
}

void ANCGameMode::PostLogin(APlayerController* NewPlayer)
{
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Begin"));
	
	Super::PostLogin(NewPlayer);

	UNetDriver* NetDriver = GetWorld()->GetNetDriver();
	if (NetDriver)
	{
		if (NetDriver->ClientConnections.Num() == 0)
		{
			NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Not ClientConnected"));
		}
		else
		{
			for (auto& Connection : NetDriver->ClientConnections)
			{
				NC_LOG(LogNetworkC, Log, TEXT("[ClientConnection:%s]"), *Connection->GetName());
				NC_LOG(LogNetworkC, Log, TEXT("[ClientController:%s]"), *Connection->OwningActor->GetName());
			}
		}
	}

	auto* PlayerState = NewPlayer->GetPlayerState<ANCPlayerState>();
	if (PlayerState)
	{
		if (NewPlayer->IsLocalPlayerController())
		{
			PlayerState->SetUserName(TEXT("Host"));
		}
		else
		{
			PlayerState->SetUserName(TEXT("Guest"));
		}
		PlayerState->OnRep_CurrentName();
	}

	if (NetDriver)
	{
		if (NetDriver->ClientConnections.Num() != 0)
		{
			NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("===============  Replication Preparation Completed On the Server  =============="));	
		}
	}
	
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("End"));
}
