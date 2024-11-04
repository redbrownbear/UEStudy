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
	DistanceThreshold = 100.f;
}

EBTNodeResult::Type UBTTask_CheckNearbyEnemies::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // 현재 AI 컨트롤러 가져오기
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    BehaviorTreeComponent = &OwnerComp;
    BlackboardComponent = OwnerComp.GetBlackboardComponent();

    // 적들을 피하기 위한 함수 호출
    return AvoidNearbyEnemies(OwnerComp);
}

EBTNodeResult::Type UBTTask_CheckNearbyEnemies::AvoidNearbyEnemies(UBehaviorTreeComponent& OwnerComp)
{
    // AI의 위치 가져오기
    AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn();
    if (!OwnerActor) return EBTNodeResult::Failed;

    FVector ActorLocation = OwnerActor->GetActorLocation();

    //UObject* CheckEnemy = BlackboardComponent->GetValueAsObject(TEXT("CheckEnemy"));
    //if (IsValid(CheckEnemy))
    //{
    //    ACharacter* Enemy = Cast<ACharacter>(CheckEnemy);
    //    if (Enemy)
    //    {
    //        float Distance = FVector::Dist(ActorLocation, Enemy->GetActorLocation());
    //        if (Distance < DistanceThreshold)
    //        {
    //            FVector AvoidDirection = (ActorLocation - Enemy->GetActorLocation()).GetSafeNormal();
    //            FVector NewLocation = ActorLocation + (AvoidDirection * DistanceThreshold);

    //            APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
    //            Proxy = UAIBlueprintHelperLibrary::CreateMoveToProxyObject(this, Pawn, NewLocation);
    //            Proxy->OnSuccess.AddDynamic(this, &ThisClass::OnResult);
    //            Proxy->OnFail.AddDynamic(this, &ThisClass::OnResult);
    //        }
    //    }
    //}

    return EBTNodeResult::Succeeded;
}

void UBTTask_CheckNearbyEnemies::OnResult(EPathFollowingResult::Type MovementResult)
{
    if (!IsValid(Proxy))
    {
        return;
    }

    FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Succeeded);
}
