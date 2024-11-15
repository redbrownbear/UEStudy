// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_CheckNearbyEnemies.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#include "Components/SplineComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/AIAsyncTaskBlueprintProxy.h"

#include "Actors/Enemy/BasicEnemy.h"

UBTTask_CheckNearbyEnemies::UBTTask_CheckNearbyEnemies()
{
	NodeName = TEXT("Check Nearby Enemies");
	DistanceThreshold = 250.0f;
}

EBTNodeResult::Type UBTTask_CheckNearbyEnemies::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    BehaviorTreeComponent = &OwnerComp;
    BlackboardComponent = OwnerComp.GetBlackboardComponent();
    SplineComponent = Cast<USplineComponent>(BlackboardComponent->GetValueAsObject(TEXT("SplineComponent")));
    check(SplineComponent);

    SplinePoints = SplineComponent->GetNumberOfSplinePoints();

    // 적들을 피하기 위한 함수 호출
    return AvoidNearbyEnemies(OwnerComp);
}

EBTNodeResult::Type UBTTask_CheckNearbyEnemies::AvoidNearbyEnemies(UBehaviorTreeComponent& OwnerComp)
{
    AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn();
    if (!OwnerActor) return EBTNodeResult::Failed;

    FVector ActorLocation = OwnerActor->GetActorLocation();

    ABasicEnemy* Enemy = Cast<ABasicEnemy>(OwnerActor);
    if (Enemy && !bAvoiding)
    {
        for (AActor* NearbyEnemy : Enemy->GetNearbyEnemies())
        {
            float Distance = FVector::Dist(ActorLocation, NearbyEnemy->GetActorLocation());
            if (Distance < DistanceThreshold)
            {
                FVector AvoidDirection = (ActorLocation - NearbyEnemy->GetActorLocation()).GetSafeNormal();
                FVector TargetLocation = ActorLocation + (AvoidDirection * 1000.0f);

                Proxy = UAIBlueprintHelperLibrary::CreateMoveToProxyObject(this, Enemy, TargetLocation);
                Proxy->OnSuccess.AddDynamic(this, &ThisClass::OnResult);
                Proxy->OnFail.AddDynamic(this, &ThisClass::OnResult);

                bAvoiding = true;
                return EBTNodeResult::InProgress;
            }
        }
    }

    return EBTNodeResult::Succeeded;
}

void UBTTask_CheckNearbyEnemies::OnResult(EPathFollowingResult::Type MovementResult)
{
    if (MovementResult == EPathFollowingResult::Success)
    {
        bAvoiding = false;  // 회피 완료 후 Spline 복귀 가능
    }

    FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Succeeded);
}
