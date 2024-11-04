// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/Pool/PooledActor.h"
#include "Particles/ParticleSystemComponent.h"

#include "Data/EffectData.h"
#include "Effect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API AEffect : public APooledActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEffect();
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);

	virtual void Play();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PlaySound();
	virtual void PlayParticle();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultSceneRoot = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleSystemComponent = nullptr;

protected: // Sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect|Sound")
	TObjectPtr<USoundBase> Sound;

	// Volume Multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect|Sound")
	float VolumeMultiplier = 1.f;

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/ProjectDD.EffectTableRow"))
	FDataTableRowHandle DataTableRowHandle;

	FEffectTableRow* EffectData;
};
