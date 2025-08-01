// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LMAPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LEAVEME_API ALMAPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ALMAPlayerController();
protected:
	void BeginPlay() override;
		virtual void BeginSpectatingState() override;
};
