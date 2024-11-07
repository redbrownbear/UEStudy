// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/HUD/DDHUDWidget.h"
#include "Actors/Items/Environment/UsableActor.h"

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
	void RemoveUsableActor(AUsableActor* NewActor);
	
protected:
	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaSeconds) override;

public:
	TArray<AUsableActor*> GetOverlappedUsableActors() { return OverlappedUsableActor; }
	void SetOverlappedUsableActor(AUsableActor* InOverlappedUsableActor) { OverlappedUsableActor.Add(InOverlappedUsableActor); }
	void SetRemoveAllUsableActor() { OverlappedUsableActor.Empty(); }

protected:
	
	class UDDHUDWidget* Widget = nullptr;
	TArray<AUsableActor*> OverlappedUsableActor;
};
