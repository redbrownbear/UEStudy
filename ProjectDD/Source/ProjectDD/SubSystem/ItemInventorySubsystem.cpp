// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/ItemInventorySubsystem.h"
#include "Data/WeaponData.h"

UItemInventorySubsystem::UItemInventorySubsystem()
{
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Data/DT_Weapon.DT_Weapon'"));
		check(Asset.Object);
		WeaponDataTable = Asset.Object;
	}
}

FDataTableRowHandle UItemInventorySubsystem::FindItem(const FName& InKey)
{
	FDataTableRowHandle DataTableRowHandle;

	bool bFind = false;
	if (WeaponDataTable->GetRowMap().Find(InKey))
	{
		check(!bFind);
		bFind = true;
		DataTableRowHandle.DataTable = WeaponDataTable;
		DataTableRowHandle.RowName = InKey;
	}

	return DataTableRowHandle;
}

FDataTableRowHandle UItemInventorySubsystem::FindItemByType(const EWeaponType WeaponType)
{
	FDataTableRowHandle DataTableRowHandle;

	if (!WeaponDataTable)
	{
		return DataTableRowHandle;
	}

	for (const auto& Row : WeaponDataTable->GetRowMap())
	{
		FWeaponTableRow* WeaponData = reinterpret_cast<FWeaponTableRow*>(Row.Value);
		if (WeaponData && WeaponData->WeaponType == WeaponType)
		{
			DataTableRowHandle.DataTable = WeaponDataTable;
			DataTableRowHandle.RowName = Row.Key;	

			break;
		}
	}

	return DataTableRowHandle;
}