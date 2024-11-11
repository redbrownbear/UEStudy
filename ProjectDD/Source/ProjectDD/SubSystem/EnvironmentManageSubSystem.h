// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/UsableActorData.h"

#include "EnvironmentManageSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UEnvironmentManageSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    UEnvironmentManageSubSystem();

public:
    UFUNCTION(BlueprintCallable)
    TArray<FUsableActorTableRow> GetUsableActorData() const;

private:
    UPROPERTY(EditAnywhere, Category = "Data")
    UDataTable* UsableActorDataTable;
};
