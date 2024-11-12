// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Data/PawnStatusData.h"

#include "UI/HUD/DDHUDWidget.h"

#include "DDHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API ADDHUD : public AHUD
{
	GENERATED_BODY()

public:
	void AddUsableActor(AUsableActor* NewActor);
	void RemoveUseActor();
	void RemoveUsableActorsAll();

public:
	void SetStatus(FPawnStatusTableRow Status);
	
protected:
	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaSeconds) override;

protected:
	
	class UDDHUDWidget* Widget = nullptr;
};
