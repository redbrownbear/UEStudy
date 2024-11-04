// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Enum/WeaponType.h"

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

protected:
	UDataTable* WeaponDataTable;
	
};
