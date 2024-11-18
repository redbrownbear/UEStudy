// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SplineComponent.h"
#include "Components/StatusComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Actors/Player/MainPlayer.h"

#include "BasicEnemyController.generated.h"

/**
 *
 */
UCLASS()
class PROJECTDD_API ABasicEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void OnDamaged(float CurrentHP, float MaxHP);

	UFUNCTION()
	void ResetOnDamaged();

	void FindPlayerByPerception();

public:
	void FindEnemyByPerception(AActor* InNearbyEnemy);
	void EraseEnemyByPerception(AActor* InNearbyEnemy);

public:
	void SetPatrolPath(TObjectPtr<USplineComponent> NewPathFinder);

private:
	void SwitchAttackDetect(AMainPlayer* DetectedPlayer, EWeaponType InWeaponType, float InDistance);

protected:
	UPROPERTY()
	TObjectPtr<USplineComponent> PathFinder;

protected:
	bool bDamaged = false;

	UPROPERTY()
	UStatusComponent* StatusComponentRef;
};
