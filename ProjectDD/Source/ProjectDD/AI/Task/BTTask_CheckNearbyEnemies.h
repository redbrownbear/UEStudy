// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_Base.h"
#include "BTTask_CheckNearbyEnemies.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UBTTask_CheckNearbyEnemies : public UBTTask_Base
{
    GENERATED_BODY()

public:
    UBTTask_CheckNearbyEnemies();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    EBTNodeResult::Type AvoidNearbyEnemies(UBehaviorTreeComponent& OwnerComp);

    UFUNCTION()
    void OnResult(EPathFollowingResult::Type MovementResult);

protected:
    UPROPERTY()
    class UAIAsyncTaskBlueprintProxy* Proxy;

    class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
    class UBlackboardComponent* BlackboardComponent = nullptr;
    class USplineComponent* SplineComponent = nullptr;

    int32 SplinePoints = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float DistanceThreshold;

    bool bAvoiding = false;
};
