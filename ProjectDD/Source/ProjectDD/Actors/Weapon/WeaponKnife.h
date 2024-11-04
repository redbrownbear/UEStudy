// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapon/BasicWeapon.h"
#include "WeaponKnife.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API AWeaponKnife : public ABasicWeapon
{
	GENERATED_BODY()

protected:
	virtual void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted) override;
	virtual void Attack() override;

};
