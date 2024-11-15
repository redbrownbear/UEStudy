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
	if (OwnerStatusComponent->Is9BulletEmpty() && OwningPawn->IsA(ABasicPlayer::StaticClass()))
	{
		UHUDManagerSubsystem* HUDManager = GetWorld()->GetGameInstance()->GetSubsystem<UHUDManagerSubsystem>();
		if (!HUDManager)
		{
			check(false);
			return;
		}

		HUDManager->ShowEmergencyMessage(TEXT("수류탄이 부족합니다."));
		return;
	}

	Super::Attack();
	OwnerStatusComponent->SetAttack(true);
}
