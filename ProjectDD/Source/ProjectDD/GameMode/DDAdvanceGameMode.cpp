// Fill out your copyright notice in the Description page of Project Settings.


#include "DDAdvanceGameMode.h"
#include "Actors/Spawner/EnemySpawner.h"
#include "Actors/Spawner/UsableActorSpawner.h"


#include "Actors/Enemy/PathFinder.h"


void ADDAdvanceGameMode::StartPlay()
{
    Super::StartPlay();

    //������ �ٲٸ� �ȵȴ�.
    //pathfinder�� �����ؼ� EnermySpawn�� ����ϴ� ����̶�...
    AEnemySpawner* Spawner = GetWorld()->SpawnActor<AEnemySpawner>(AEnemySpawner::StaticClass());
    if (Spawner)
    {
        UE_LOG(LogTemp, Log, TEXT("Spawner created successfully."));
    }

    AUsableActorSpawner* ActorSpawner = GetWorld()->SpawnActor<AUsableActorSpawner>(AUsableActorSpawner::StaticClass());
    if (Spawner)
    {
        UE_LOG(LogTemp, Log, TEXT("Spawner created successfully."));
    }
}