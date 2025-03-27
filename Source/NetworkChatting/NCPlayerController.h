// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NCPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NETWORKCHATTING_API ANCPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANCPlayerController();

	// Getter Setter
	FString GetUserName() const;
	void SetUserName(const FString& NewUserName);
	UUserWidget* GetHUDWidget() const;

	// RPC 관련
	UFUNCTION(Server, Reliable)
	void ServerRPCSendMessageToString(const FString& ReceivedMessage);

	// Replication
	UFUNCTION()
	void OnRep_CurrentName() const;

	//
	void SendNetworkMessage(const FString& MessageToSend);
	void HandleAddServerChatLog(const FString& MessageToSend) const;
	
protected:
	// Widget 관련
	void InitWidget();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY()
	UUserWidget* HUDWidgetInstance;
	
	// Replication 관련
	UPROPERTY(ReplicatedUsing = OnRep_CurrentName, EditDefaultsOnly, BlueprintReadOnly, Category = "MessageState")
	FString UserName;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	// LifeCycle
	virtual void BeginPlay() override;
	virtual void PostNetInit() override;
};


