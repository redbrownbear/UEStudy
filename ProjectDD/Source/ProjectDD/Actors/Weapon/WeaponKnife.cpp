// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/WeaponKnife.h"
#include "Data/WeaponData.h"

void AWeaponKnife::Attack()
{
	APlayerController* PlayerController = Cast<APlayerController>(OwningPawn->GetController());
	if (PlayerController)
	{
		PlayerController->DisableInput(PlayerController);
	}

	OwnerStatusComponent->SetFixedAttack(true);
	Super::Attack();
}
