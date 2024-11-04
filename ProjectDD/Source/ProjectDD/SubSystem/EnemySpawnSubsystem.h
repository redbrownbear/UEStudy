// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/EnemySpawnData.h"

#include "EnemySpawnSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UEnemySpawnSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UEnemySpawnSubsystem();

public:
    UFUNCTION(BlueprintCallable)
    TArray<FEnemySpawnTableRow> GetEnemySpawnData() const;

private:
    UPROPERTY(EditAnywhere, Category = "Data")
    UDataTable* EnemySpawnDataTable;
};

