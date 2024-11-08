// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Data/EnemySpawnData.h"

#include "EnemySpawner.generated.h"

UCLASS()
class PROJECTDD_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	void SetEnemy();
	void SpawnEnemy(const FEnemySpawnTableRow& InSpawnData, const FDataTableRowHandle& InPawnHandle);
};
