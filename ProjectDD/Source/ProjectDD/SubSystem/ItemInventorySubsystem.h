// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Enum/WeaponType.h"
#include "Enum/KeyItemType.h"
#include "Actors/Items/Environment/UsableActor.h"

#include "ItemInventorySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UItemInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UItemInventorySubsystem();

	FDataTableRowHandle FindItem(const FName& InKey);
	FDataTableRowHandle FindItemByType(const EWeaponType InWeaponType);

	void AddItem(FUsableActorTableRow InUsableActor);
	void RemoveItem(FUsableActorTableRow* InUsableActor);

	TArray<TUniquePtr<FUsableActorTableRow>>& GetUsableActorData() { return arrUsableActor; }

	const FUsableActorTableRow* GetKeyByType(EKeyItemType InType) const;

protected:
	UDataTable* WeaponDataTable;

	TArray<TUniquePtr<FUsableActorTableRow>> arrUsableActor;
};
