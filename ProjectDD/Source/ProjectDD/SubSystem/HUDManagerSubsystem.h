// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "Actors/Items/Environment/UsableActor.h"
#include "UI/HUD/DDHUD.h"

#include "HUDManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UHUDManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void SetHUD();

//일반 물체와 상호작용 대한 매니징()
public:
	TArray<AUsableActor*> GetOverlappedUsableActors() { return OverlappedUsableActor; }
	
	void AddOverlappedUsableActor(AUsableActor* InOverlappedUsableActor);
	void RemoveUnUsebleActor(AUsableActor* InUnUsableActor);
	void RemoveAllUsableActor();

//PlayerStatus에 대한 매니징
public:
	void SetStatus(FPawnStatusTableRow Status);
	void DrawStatusUI();

	void ShowEmergencyMessage(const FString& Message);
	void ShowDie();

private:
	ADDHUD* HUD;
	TArray<AUsableActor*> OverlappedUsableActor;
	FPawnStatusTableRow PlayerStatusData;
};
