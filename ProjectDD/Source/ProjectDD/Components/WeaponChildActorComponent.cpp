// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponChildActorComponent.h"
#include "Actors/Weapon/BasicWeapon.h"

UWeaponChildActorComponent::UWeaponChildActorComponent()
{
	SetChildActorClass(ABasicWeapon::StaticClass());
}

void UWeaponChildActorComponent::SetData(FDataTableRowHandle InDataTableRowHandle)
{
	if (InDataTableRowHandle.IsNull()) { return; }
	FWeaponTableRow* Data = InDataTableRowHandle.GetRow<FWeaponTableRow>(TEXT("Weapon"));
	if (!Data) { ensure(false); return; }

	if (GetChildActorClass() != Data->WeaponClass)
	{
		SetChildActorClass(Data->WeaponClass);
	}

	if (Data->WeaponType == EWeaponType::WT_None)
		return;


	ABasicWeapon* Weapon = Cast<ABasicWeapon>(GetChildActor());
	check(Weapon);
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	check(OwnerPawn);
	Weapon->SetOwner(OwnerPawn);
	Weapon->SetInstigator(OwnerPawn);
	Weapon->SetData(InDataTableRowHandle);
}
