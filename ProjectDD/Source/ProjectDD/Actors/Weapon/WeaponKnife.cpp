// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/WeaponKnife.h"
#include "Data/WeaponData.h"

void AWeaponKnife::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	if (WeaponTableRow && WeaponTableRow->WeaponAttackMontage == Montage)
	{
		OwnerStatusComponent->SetAttack(false);

		APlayerController* PlayerController = Cast<APlayerController>(OwningPawn->GetController());
		if (PlayerController)
		{
			PlayerController->EnableInput(PlayerController);
		}
	}
}

void AWeaponKnife::Attack()
{
	Super::Attack();

	OwnerStatusComponent->SetAttack(true);

	APlayerController* PlayerController = Cast<APlayerController>(OwningPawn->GetController());
	if (PlayerController)
	{
		PlayerController->DisableInput(PlayerController);
	}
}
