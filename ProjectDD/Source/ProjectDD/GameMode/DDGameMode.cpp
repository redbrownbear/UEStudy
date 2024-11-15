// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/DDGameMode.h"
#include "Actors/Spawner/EnemySpawner.h"
#include "Actors/Spawner/UsableActorSpawner.h"

#include "Actors/Enemy/PathFinder.h"


void ADDGameMode::StartPlay()
{
    Super::StartPlay();

    //순서를 바꾸면 안된다.
    //pathfinder를 생성해서 EnermySpawn때 사용하는 방식이라...
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
