// Fill out your copyright notice in the Description page of Project Settings.


#include "Handler/ItemEquipHandler.h"
#include "Subsystem/ItemInventorySubsystem.h"
#include "Actors/Weapon/BasicWeapon.h"
#include "GameFramework/Character.h"
#include "Components/WeaponChildActorComponent.h"

void UItemEquipHandler::Equip()
{
	if (UWorld* World = Context->User->GetWorld())
	{
		UItemInventorySubsystem* Subsystem = World->GetGameInstance()->GetSubsystem<UItemInventorySubsystem>();
		FDataTableRowHandle Handle = Subsystem->FindItemByType(Context->ItemType);
		if (Handle.IsNull())
		{
			ensureMsgf(false, TEXT("Handle is not valid"));
			return;
		}

		APawn* Pawn = Context->User->GetPawn();
		UWeaponChildActorComponent* Weapon = Pawn->GetComponentByClass<UWeaponChildActorComponent>();
		check(Weapon);
		Weapon->SetData(Handle);
	}

	ReleaseContext();
}

void UItemEquipHandler::Unequip()
{
	ReleaseContext();
}
