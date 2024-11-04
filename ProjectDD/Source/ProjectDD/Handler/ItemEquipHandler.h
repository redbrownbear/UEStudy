// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enum/WeaponType.h"

#include "ItemEquipHandler.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTDD_API UItemEquipHandler : public UObject
{
	GENERATED_BODY()
public:
	struct FItemContext
	{
		// Item을 사용하는 주체
		APlayerController* User;
		EWeaponType ItemType;
	};
	using FContext = FItemContext;

public:
	void SetContext(TUniquePtr<FContext> NewContext) { check(!Context); Context = MoveTemp(NewContext); }

public:
	virtual void Equip();
	virtual void Unequip();

private:
	void ReleaseContext() { check(Context); Context = nullptr; }

protected:
	TUniquePtr<FContext> Context;
	
};
