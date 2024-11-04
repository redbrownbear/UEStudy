// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/EnemySpawnSubsystem.h"

UEnemySpawnSubsystem::UEnemySpawnSubsystem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Data/DT_EnemySpawn.DT_EnemySpawn'"));
	check(Asset.Object);
	EnemySpawnDataTable = Asset.Object;

}

TArray<FEnemySpawnTableRow> UEnemySpawnSubsystem::GetEnemySpawnData() const
{
	TArray<FEnemySpawnTableRow> SpawnDataArray;

    if (EnemySpawnDataTable)
    {
        // 데이터 테이블의 모든 행 가져오기
        for (const auto& Row : EnemySpawnDataTable->GetRowMap())
        {
            FEnemySpawnTableRow* SpawnData = (FEnemySpawnTableRow*)Row.Value;
            if (SpawnData)
            {
                SpawnDataArray.Add(*SpawnData);
            }
        }
    }

    return SpawnDataArray;
}
