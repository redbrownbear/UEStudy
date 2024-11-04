// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EWeaponType : uint8
{
	WT_None     UMETA(DisplayName = "None"),
	WT_Knife    UMETA(DisplayName = "Knife"),
	WT_Pistol   UMETA(DisplayName = "Pistol"),
	WT_Rifle    UMETA(DisplayName = "Rifle"),
	WT_Grenade  UMETA(DisplayName = "Grenade"),
};
