// Fill out your copyright notice in the Description page of Project Settings.


#include "NCHUD.h"
#include "NCPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "NetworkChatting.h"

ANCHUD::ANCHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDWidget(TEXT("/Game/Blueprints/BP_NCWidget.BP_NCWidget_C"));
	if (HUDWidget.Succeeded())
	{
		UserWidgetClass = HUDWidget.Class;
	}
	
}

void ANCHUD::SetReadyMessage(FString NewMessage)
{
	ReadyMessage = NewMessage;
}

FString ANCHUD::GetReadyMessage() const
{
	return ReadyMessage;
}

void ANCHUD::BeginPlay()
{
	Super::BeginPlay();

	if (UserWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), UserWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
		}
	}
	
	NC_LOG(LogNetworkC, Log, TEXT("[%s / Owner:%s]"), *GetName(), *GetOwner()->GetName());
}
