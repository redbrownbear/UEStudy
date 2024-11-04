// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileData.generated.h"

class ABasicProjectile;

/**
 * 
 */
USTRUCT()
struct PROJECTDD_API FProjectileTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	FTransform Transform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<ABasicProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float MaxSpeed;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float GravityScale;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float LifeSpan;

	UPROPERTY(EditAnywhere, Category = "Projectile|Effect", meta = (RowType = "/Script/ProjectDD.EffectTableRow"))
	FDataTableRowHandle HitEffectTableRowHandle;
};
