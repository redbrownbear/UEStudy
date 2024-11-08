// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnStatusData.generated.h"

/**
 * 
 */
USTRUCT()
struct PROJECTDD_API FPawnStatusTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Status")
	float HP;

	UPROPERTY(EditAnywhere, Category = "Status")
	float MAXHP;

	UPROPERTY(EditAnywhere, Category = "Status")
	int32 MeleeAttackPoint;

	UPROPERTY(EditAnywhere, Category = "Status")
	int32 BulletCount9mm;

	UPROPERTY(EditAnywhere, Category = "Status")
	int32 BulletCount556mm;
};
