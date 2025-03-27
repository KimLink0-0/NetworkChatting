#include "NCPlayerController.h"

#include "NCGameState.h"
#include "NCHUDWidget.h"
#include "NCMessageBoxWidget.h"
#include "NetworkChatting.h"
#include "Net/UnrealNetwork.h"

ANCPlayerController::ANCPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDWidget(TEXT("/Game/Blueprints/WBP_NCHUDWidget.WBP_NCHUDWidget_c"));
	if (HUDWidget.Succeeded())
	{
		HUDWidgetClass = HUDWidget.Class;
	}
	
	HUDWidgetInstance = nullptr;
}


FString ANCPlayerController::GetUserName() const
{
	return UserName;
}

void ANCPlayerController::SetUserName(const FString& NewUserName)
{
	UserName = NewUserName;
}

UUserWidget* ANCPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void ANCPlayerController::SendNetworkMessage(const FString& MessageToSend)
{
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Begin"));

	if (HasAuthority())
	{
		HandleAddServerChatLog(MessageToSend);
	}
	else
	{
		ServerRPCSendMessageToString(MessageToSend);
	}

	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("End"));
}

void ANCPlayerController::HandleAddServerChatLog(const FString& MessageToSend)
{
	auto* GameState = Cast<ANCGameState>(GetWorld()->GetGameState());
	if (GameState)
	{
		GameState->AddServerChatLog(MessageToSend);
		TArray<FString> ReceivedMessage = GameState->GetServerChatLog();
		HandleMulticastRPCShowReceivedMessage(ReceivedMessage);
	}
}

void ANCPlayerController::ServerRPCSendMessageToString_Implementation(const FString& ReceivedMessage)
{
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Begin"));
	
	HandleAddServerChatLog(ReceivedMessage);

	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("End"));
}

void ANCPlayerController::HandleMulticastRPCShowReceivedMessage(const TArray<FString>& ReceivedMessage)
{
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Begin"));
	
	MulticastRPCShowReceivedMessage(ReceivedMessage);

	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("End"));
}


void ANCPlayerController::MulticastRPCShowReceivedMessage_Implementation(const TArray<FString>& ReceivedMessage)
{
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Begin"));
	auto* NCHUDWidget = Cast<UNCHUDWidget>(HUDWidgetInstance);
	if (NCHUDWidget)
	{
		NCHUDWidget->MessageBoxWidget->UpdateChattingLog(ReceivedMessage);
	}
	else
	{
		NC_LOG(LogNetworkC, Warning, TEXT("HUDWidgetInstance is null"));
	}
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("End"));
}


void ANCPlayerController::OnRep_CurrentName() const
{
	NC_LOG(LogNetworkC, Log, TEXT("[%s :%s]"), *GetName(), TEXT("========= Begin ========="));
	
	NC_LOG(LogNetworkC, Log, TEXT("[%s UserName:%s]"), *GetName(), *GetUserName())
	
	NC_LOG(LogNetworkC, Log, TEXT("[%s :%s]"), *GetName(), TEXT("========== End =========="));
}


void ANCPlayerController::InitWidget()
{
	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
		}
	}
}

void ANCPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANCPlayerController, UserName);
}


void ANCPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	InitWidget();
	bShowMouseCursor = true;
	
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