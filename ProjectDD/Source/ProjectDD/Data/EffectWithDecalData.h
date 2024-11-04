// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/EffectData.h"
#include "EffectWithDecalData.generated.h"

/**
 * 
 */
USTRUCT()
struct PROJECTDD_API FEffectWithDecalTableRow : public FEffectTableRow
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Effect|Decal")
	FTransform DecalTransform;
	UPROPERTY(EditAnywhere, Category = "Effect|Decal")
	UMaterial* DecalMaterial;
};