// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DDGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API ADDGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	//필요한 
public:
	virtual void StartPlay() override;
};
