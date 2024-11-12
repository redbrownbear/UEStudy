// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/BTTask_Base.h"
#include "Components/WeaponChildActorComponent.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UBTTask_Attack : public UBTTask_Base
{
	GENERATED_BODY()

public:
	UBTTask_Attack();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    EBTNodeResult::Type Attack(UBehaviorTreeComponent& OwnerComp);

    UFUNCTION()
    void OnResult(EPathFollowingResult::Type MovementResult);

    class UAIAsyncTaskBlueprintProxy* Proxy;

    class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
    class UBlackboardComponent* BlackboardComponent = nullptr;
    class UWeaponChildActorComponent* WeaponComponent = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float DistanceThreshold;
	
};
