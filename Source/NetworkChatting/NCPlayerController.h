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
	virtual void BeginPlay() override;

	virtual void PostNetInit() override;
};
