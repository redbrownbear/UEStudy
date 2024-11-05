// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Items/Environment/UsableActor.h"
#include "UsableDoor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API AUsableDoor : public AUsableActor
{
	GENERATED_BODY()
	
protected:
	virtual void OnItemUse(bool isUsed) override;


protected:
	float LocalRotation;

};
