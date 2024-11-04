// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectData.generated.h"

/**
 * 
 */
USTRUCT()
struct PROJECTDD_API FEffectTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	//UPROPERTY(EditAnywhere, Category = "Effect")
	//TSubclassOf<AEffect> EffectClass;

public:
	UPROPERTY(EditAnywhere, Category = "Effect|Sound")
	TObjectPtr<USoundBase> Sound;
	UPROPERTY(EditAnywhere, Category = "Effect|Sound")
	float VolumeMultiplier = 1.f;

public:
	UPROPERTY(EditAnywhere, Category = "Effect|Particle")
	TObjectPtr<UParticleSystem> Particle;

	UPROPERTY(EditAnywhere, Category = "Effect|Particle")
	FTransform ParticleTransform = FTransform::Identity;
};