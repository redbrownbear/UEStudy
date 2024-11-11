// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/UsableActorData.h"

#include "UsableActorSpawner.generated.h"

UCLASS()
class PROJECTDD_API AUsableActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUsableActorSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	void SetUsableActor();
	void SpawnUsableActor(const FUsableActorTableRow& InSpawnData);

};
