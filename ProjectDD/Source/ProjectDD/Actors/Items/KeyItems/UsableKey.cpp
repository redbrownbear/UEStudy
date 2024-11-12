// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/KeyItems/UsableKey.h"
#include "SubSystem/HUDManagerSubsystem.h"
#include "SubSystem/ItemInventorySubsystem.h"

void AUsableKey::OnItemUse(bool isUsable)
{
	UHUDManagerSubsystem* HUDManager = GetWorld()->GetGameInstance()->GetSubsystem<UHUDManagerSubsystem>();
	if (!HUDManager)
	{
		check(false);
		return;
	}

	HUDManager->RemoveUnUsebleActor(this);
	Destroy();
}
