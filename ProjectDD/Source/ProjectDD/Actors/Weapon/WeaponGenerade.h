// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapon/BasicWeapon.h"
#include "WeaponGenerade.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API AWeaponGenerade : public ABasicWeapon
{
	GENERATED_BODY()

	virtual void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted) override;
	virtual void Attack() override;
	
};
