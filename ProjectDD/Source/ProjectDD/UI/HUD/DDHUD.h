// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Data/PawnStatusData.h"

#include "UI/InGame/UI_InGameWidget.h"

#include "DDHUD.generated.h"

enum class HUDState
{
	Login,
	InGame,

	End,
};


/**
 * 
 */
UCLASS()
class PROJECTDD_API ADDHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaSeconds) override;


public:
	void AddUsableActor(AUsableActor* NewActor);
	void RemoveUseActor();
	void RemoveUsableActorsAll();

public:
	void SetStatus(FPawnStatusTableRow Status);
	void ShowEmergencyStatus(const FString& Message);
	void ShowDie();
	
protected:
	
	class UUI_InGameWidget* Widget = nullptr;
};
