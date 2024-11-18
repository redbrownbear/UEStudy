// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Data/ProjectileData.h"
#include "Enum/WeaponType.h"
#include "Sound/SoundCue.h"

#include "BasicGrenade.generated.h"


UCLASS()
class PROJECTDD_API ABasicGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicGrenade();

	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);

	void ProjectileFire(APawn* InOwner, EWeaponType InWeaponType, int32 InCount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnExplode();
	virtual void OnExplosionFinished();


protected:
	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY()
	UProjectileMovementComponent* ProjectileMovementComponent;

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/ProjectDD.ProjectileTableRow"))
	FDataTableRowHandle DataTableRowHandle;

	FProjectileTableRow* ProjectileData;

	UParticleSystem* ExplosionEffect;
	USoundCue* ExplosionSound;
	float ExplosionRadius;
	float ExplosionDamage;
	float FuseTime;

	FTimerHandle FuseTimerHandle;
	FTimerHandle ExplosionTimerHandle;
};
