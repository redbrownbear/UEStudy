// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/WeaponGenerade.h"

void AWeaponGenerade::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	if (WeaponTableRow && WeaponTableRow->WeaponAttackMontage == Montage)
	{
		OwnerStatusComponent->SetAttack(false);
	}
}

void AWeaponGenerade::Attack()
{
	OwnerStatusComponent->SetAim(true);

	Super::Attack();

	OwnerStatusComponent->SetAttack(true);
}
