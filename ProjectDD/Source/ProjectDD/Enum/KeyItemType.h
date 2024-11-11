// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EKeyItemType : uint8
{
	Key_None	UMETA(DisplayName = "NoKey"),
	Key_Yellow  UMETA(DisplayName = "YellowKey"),
	Key_Blue    UMETA(DisplayName = "BlueKey"),
	Key_Red		UMETA(DisplayName = "RedKey"),
};
