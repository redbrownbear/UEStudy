// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Effect/Effect.h"
#include "Components/DecalComponent.h"
#include "Data/EffectWithDecalData.h"
#include "EffectWithDecal.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API AEffectWithDecal : public AEffect
{
	GENERATED_BODY()
public:
	AEffectWithDecal();
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UDecalComponent* HitDecalComponent;

protected:
	FEffectWithDecalTableRow* EffectWithDecalData;
};
