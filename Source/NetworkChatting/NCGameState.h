// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "NCGameState.generated.h"

#define LOG_NETMODEINFO ((GetNetMode() == ENetMode::NM_Client) ? *FString::Printf(TEXT("Client%d"), GPlayInEditorID) : ((GetNetMode() == ENetMode::NM_Standalone) ? TEXT("Standalone") : TEXT("Server")))
#define LOG_CALLINFO ANSI_TO_TCHAR(__FUNCTION__)
#define NC_LOG(LogCat, Verbosity, Format, ...) UE_LOG(LogCat, Verbosity, TEXT("[NetMode:%s] %s %s"), LOG_NETMODEINFO, LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
DECLARE_LOG_CATEGORY_EXTERN(NetworkChatting, Log, All);

UCLASS()
class NETWORKCHATTING_API ANCGameState : public AGameState
{
	GENERATED_BODY()
	
};
