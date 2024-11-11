// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/EnvironmentManageSubSystem.h"

UEnvironmentManageSubSystem::UEnvironmentManageSubSystem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Data/DT_UsableActor.DT_UsableActor'"));
	check(Asset.Object);
	UsableActorDataTable = Asset.Object;
}

TArray<FUsableActorTableRow> UEnvironmentManageSubSystem::GetUsableActorData() const
{
    TArray<FUsableActorTableRow> SpawnDataArray;

    if (UsableActorDataTable)
    {
        // 데이터 테이블의 모든 행 가져오기
        for (const auto& Row : UsableActorDataTable->GetRowMap())
        {
            FUsableActorTableRow* SpawnData = (FUsableActorTableRow*)Row.Value;
            if (SpawnData)
            {
                SpawnDataArray.Add(*SpawnData);
            }
        }
    }

    return SpawnDataArray;
}
