// Fill out your copyright notice in the Description page of Project Settings.


#include "NCPlayerController.h"
#include "NetworkChatting.h"

void ANCPlayerController::BeginPlay()
{
	// NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Begin"));
	//
	// if (HasAuthority())
	// {
	// 	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("[ServerController]BeginPlay"));
	// }
	// else
	// {
	// 	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("[ClientController]BeginPlay"));
	// }
	//
	Super::BeginPlay();

	// 마우스 커서 사용 설정
	bShowMouseCursor = true;
	
	// if (IsLocalPlayerController())
	// {
	// 	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Can Use MouseCursor"));	
	// }
	//
	// NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("End"));
}

void ANCPlayerController::PostNetInit()
{
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Begin"));
	
	Super::PostNetInit();

	UNetDriver* NetDriver = GetWorld()->GetNetDriver();
	if (NetDriver)
	{
		if (NetDriver->ServerConnection)
		{
			NC_LOG(LogNetworkC, Log, TEXT("[ServerConnection:%s]"), *NetDriver->ServerConnection->GetName());
			NC_LOG(LogNetworkC, Log, TEXT("[ServerController:%s]"), *GetName());
		}
		else
		{
			NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Not ServerConnected"));
		}
	}

	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("End"));
}


