// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitlePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API ATitlePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

};
