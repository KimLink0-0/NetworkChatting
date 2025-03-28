// Fill out your copyright notice in the Description page of Project Settings.


#include "NCGameState.h"

#include "NCPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "NetworkChatting.h"
#include "NCHUDWidget.h"
#include "NCMessageBoxWidget.h"

TArray<FString> ANCGameState::GetServerChatLog() const
{
	return ServerChatLog;
}

void ANCGameState::AddServerChatLog(const FString& NewChatMessage)
{
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Begin"));
	
	ServerChatLog.Add(NewChatMessage);
	
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("End"));
}

void ANCGameState::UpdateServerChatLog() const
{
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Begin"));
	
	auto* PlayerContoller = Cast<ANCPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerContoller)
	{
		auto* NCHUDWidget = PlayerContoller->GetHUDWidget();
		if (NCHUDWidget)
		{
			NCHUDWidget->MessageBoxWidget->UpdateChattingLog(ServerChatLog);
		}	
	}

	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("End"));
}

void ANCGameState::OnRep_ServerChatLog() const
{
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Replicated ChatLog"));
	
}

void ANCGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANCGameState, ServerChatLog)
}
