// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/ItemInventorySubsystem.h"
#include "Data/WeaponData.h"

UItemInventorySubsystem::UItemInventorySubsystem()
{
	//초기에 테이블에서 가져오는게 아니라 데이터를 불러오는형식 이게 맞다
	//캐릭터 정보를 불러오는 것으로 최종 변환 해야함!

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

void UItemInventorySubsystem::AddItem(const AUsableActor& InUsableActor)
{

}
