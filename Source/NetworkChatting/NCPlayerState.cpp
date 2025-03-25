// Fill out your copyright notice in the Description page of Project Settings.


#include "NCPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "NetworkChatting.h"

FString ANCPlayerState::GetUserName() const
{
	return UserName;
}

void ANCPlayerState::SetUserName(FString NewControllerName)
{
	UserName = NewControllerName;
}

FString ANCPlayerState::GetInitialReadyText() const
{
	return InitialReadyText;
}

void ANCPlayerState::SetInitialReadyText(FString NewInitialReadyText)
{
	InitialReadyText = NewInitialReadyText;
}

void ANCPlayerState::OnRep_CurrentName()
{
	NC_LOG(LogNetworkC, Log, TEXT("[%s :%s]"), *GetName(), TEXT("========= Begin ========="));
	SetInitialReadyText(GetUserName());

	if (GetOwner())
	{
		NC_LOG(LogNetworkC, Log, TEXT("[%s Owner:%s]"), *GetName(), *GetOwner()->GetName());	
	}
	NC_LOG(LogNetworkC, Log, TEXT("[%s UserName:%s]"), *GetName(), *GetUserName())
	NC_LOG(LogNetworkC, Log, TEXT("[%s InitialReadyText:%s]"), *GetName(), *GetInitialReadyText())
	
	NC_LOG(LogNetworkC, Log, TEXT("[%s :%s]"), *GetName(), TEXT("========== End =========="));
}

void ANCPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ANCPlayerState, UserName, COND_InitialOnly);
}


