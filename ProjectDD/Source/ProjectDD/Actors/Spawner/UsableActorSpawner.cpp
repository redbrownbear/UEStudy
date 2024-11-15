// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Spawner/UsableActorSpawner.h"
#include "Actors/Items/Environment/UsableActor.h"
#include "SubSystem/EnvironmentManageSubSystem.h"
#include "NavigationSystem.h"

// Sets default values
AUsableActorSpawner::AUsableActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUsableActorSpawner::BeginPlay()
{
	Super::BeginPlay();

	SetFolderPath(FName("FunctionOnly"));
	SetUsableActor();
}

void AUsableActorSpawner::SetUsableActor()
{
    UEnvironmentManageSubSystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UEnvironmentManageSubSystem>();

    if (Subsystem)
    {
        TArray<FUsableActorTableRow> SpawnDataArray = Subsystem->GetUsableActorData();

        if (SpawnDataArray.Num() <= 0)
            return;

        for (FUsableActorTableRow tableData : SpawnDataArray)
        {
            SpawnUsableActor(tableData);
        }
    }
}

void AUsableActorSpawner::SpawnUsableActor(const FUsableActorTableRow& InSpawnData)
{
    AUsableActor* SpawnedActor= GetWorld()->SpawnActor<AUsableActor>(InSpawnData.UsableActor, InSpawnData.MeshTransform);
    if (SpawnedActor)
    {
        UE_LOG(LogTemp, Log, TEXT("Enemy spawned at location"));
    }

    SpawnedActor->SetData(InSpawnData);

    UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (NavSystem)
    {
        NavSystem->Build();
    }
}

