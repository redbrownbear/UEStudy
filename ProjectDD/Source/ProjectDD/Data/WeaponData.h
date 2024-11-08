// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animation/BaisicCharacterAnimInstance.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StatusComponent.h"
#include "Misc/Utils.h"
#include "Enum/WeaponType.h"
#include "WeaponData.generated.h"

class ABasicWeapon;

USTRUCT()
struct PROJECTDD_API FWeaponTableRow : public FTableRowBase
{
	GENERATED_BODY()
	FWeaponTableRow()
	{

	}

public: // Base
	UPROPERTY(EditAnywhere, Category = "Weapon")
	USkeletalMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FTransform Transform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<ABasicWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	EWeaponType WeaponType;

public: //Effect
	UPROPERTY(EditAnywhere, Category = "Effect")
	UParticleSystem* ParticleSystem;

public: // Animation
	UPROPERTY(EditAnywhere, Category = "Animation")
	TSubclassOf<UBaisicCharacterAnimInstance> AnimClass;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* WeaponAttackMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TArray<UAnimMontage*> HitReactMontage;

public: //Projectile
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/ProjectDD.ProjectileTableRow"))
	FDataTableRowHandle ProjectileRowHandle;

};