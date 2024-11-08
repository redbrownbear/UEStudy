// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Player/BasicPlayer.h"

#include "UI/HUD/DDHUD.h"
#include "MainPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API AMainPlayer : public ABasicPlayer
{
	GENERATED_BODY()
	

public:
	AMainPlayer();

protected:
	virtual void Tick(float DeltaTime) override;

protected:
	void CheckForInteractableActor();

protected:
	UPROPERTY()
	ADDHUD* HUD = nullptr;

	FCollisionShape BoxShape;

	FCollisionQueryParams Params;
};
