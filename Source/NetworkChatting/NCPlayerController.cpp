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

UNCHUDWidget* ANCPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void ANCPlayerController::SendNetworkMessage(const FString& MessageToSend)
{
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Begin"));


	ServerRPCSendMessageToString(MessageToSend);
	

	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("End"));
}


void ANCPlayerController::ServerRPCSendMessageToString_Implementation(const FString& ReceivedMessage)
{
	NC_LOG(LogNetworkC, Log, TEXT("%s"), TEXT("Begin"));

	auto* GameState = Cast<ANCGameState>(GetWorld()->GetGameState());
	if (GameState)
	{
		GameState->AddServerChatLog(ReceivedMessage);
		TArray<FString> CurrentChattingLog = GameState->GetServerChatLog();
		MulticastRPCShowReceivedMessage(CurrentChattingLog);
	}
	
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
		HUDWidgetInstance = CreateWidget<UNCHUDWidget>(GetWorld(), HUDWidgetClass);
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

	// 서버에서 위젯 중복 생성을 방지
	if (IsLocalController())
	{
		InitWidget();	
	}
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