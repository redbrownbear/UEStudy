// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/DDHUDWidget.h"

#include "DDHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API ADDHUD : public AHUD
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	class UDDHUDWidget* Widget = nullptr;

};
