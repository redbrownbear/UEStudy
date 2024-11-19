// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySpawnData.generated.h"

class ABasicEnemy;
/**
 * 
 */
USTRUCT()
struct PROJECTDD_API FEnemySpawnTableRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "SpawnData")
    TSubclassOf<ABasicEnemy> EnemyClass;

    UPROPERTY(EditAnywhere, Category = "SpawnData")
    FVector SpawnLocation;

    UPROPERTY(EditAnywhere, Category = "SpawnData")
    FRotator SpawnRotation;

    UPROPERTY(EditAnywhere, Category = "SpawnData")
    float SpawnType;

    UPROPERTY(EditAnywhere, meta = (RowType = "/Script/ProjectDD.PawnTableRow"))
    FDataTableRowHandle EnemyDataHandle;
};