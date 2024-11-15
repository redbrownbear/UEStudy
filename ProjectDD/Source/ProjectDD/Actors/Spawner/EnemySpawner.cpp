// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Spawner/EnemySpawner.h"
#include "Actors/Enemy/BasicEnemy.h"

#include "SubSystem/EnemySpawnSubsystem.h"
#include "NavigationSystem.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	SetFolderPath(FName("FunctionOnly"));

    SetEnemy();
}

void AEnemySpawner::SetEnemy()
{
    UEnemySpawnSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UEnemySpawnSubsystem>();

    if (Subsystem)
    {
        TArray<FEnemySpawnTableRow> SpawnDataArray = Subsystem->GetEnemySpawnData();

        if (SpawnDataArray.Num() <= 0)
            return;

        for (FEnemySpawnTableRow tableData : SpawnDataArray)
        {
            SpawnEnemy(tableData, tableData.EnemyDataHandle);
        }
    }
}

void AEnemySpawner::SpawnEnemy(const FEnemySpawnTableRow& InSpawnData, const FDataTableRowHandle& InPawnHandle) 
{
    ABasicEnemy* SpawnedEnemy = GetWorld()->SpawnActor<ABasicEnemy>(InSpawnData.EnemyClass, InSpawnData.SpawnLocation, InSpawnData.SpawnRotation);
    if (SpawnedEnemy)
    {       
        UE_LOG(LogTemp, Log, TEXT("Enemy spawned at location"));
    }

    SpawnedEnemy->SpawnData(InPawnHandle, InPawnHandle.RowName);
    SpawnedEnemy->InitAdditional();

    UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (NavSystem)
    {
        NavSystem->UpdateActorInNavOctree(*SpawnedEnemy);
        NavSystem->Build();
    }
}


