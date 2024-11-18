// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/WeaponGenerade.h"

void AWeaponGenerade::Attack()
{
	if (OwnerStatusComponent->IsGrenadeEmpty() && OwningPawn->IsA(ABasicPlayer::StaticClass()))
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

	APlayerController* PlayerController = Cast<APlayerController>(OwningPawn->GetController());
	if (PlayerController)
	{
		PlayerController->DisableInput(PlayerController);
	}

	OwnerStatusComponent->SetFixedAttack(true);
	Super::Attack();
}
