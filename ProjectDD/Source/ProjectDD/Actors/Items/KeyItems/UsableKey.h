// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Items/Environment/UsableActor.h"
#include "UsableKey.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API AUsableKey : public AUsableActor
{
	GENERATED_BODY()

	virtual void OnItemUse(bool isUsable) override;
	
};
