// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NCPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class NETWORKCHATTING_API ANCPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	FString GetUserName() const;
	void SetUserName(FString NewControllerName);
	FString GetInitialReadyText() const;
	void SetInitialReadyText(FString NewInitialReadyText);

	UPROPERTY(ReplicatedUsing = OnRep_CurrentName, EditDefaultsOnly, BlueprintReadOnly, Category = "MessageState")
	FString UserName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MessageState")
	FString InitialReadyText;

	UFUNCTION()
	void OnRep_CurrentName();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
};