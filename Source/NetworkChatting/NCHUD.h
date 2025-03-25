// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NCHUD.generated.h"

/**
 * 
 */
UCLASS()
class NETWORKCHATTING_API ANCHUD : public AHUD
{
	GENERATED_BODY()

public:
	ANCHUD();
	
	void SetReadyMessage(FString NewMessage);
	FString GetReadyMessage() const;

protected:
	FString ReadyMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HUD")
	FString WrittenMessage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<UUserWidget> UserWidgetClass;

	UPROPERTY()
	UUserWidget* HUDWidgetInstance;

	virtual void BeginPlay() override;
};
