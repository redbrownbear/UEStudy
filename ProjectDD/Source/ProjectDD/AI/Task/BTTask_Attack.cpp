// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_Attack.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/AIAsyncTaskBlueprintProxy.h"
#include "Actors/Weapon/BasicWeapon.h"

UBTTask_Attack::UBTTask_Attack()
{
    NodeName = TEXT("Attack");
    DistanceThreshold = 1000.0f;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // 현재 AI 컨트롤러 가져오기
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    BehaviorTreeComponent = &OwnerComp;
    BlackboardComponent = OwnerComp.GetBlackboardComponent();

    BehaviorTreeComponent = &OwnerComp;

    AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn();
    if (!OwnerActor) return EBTNodeResult::Failed;

    WeaponComponent = OwnerActor->FindComponentByClass<UWeaponChildActorComponent>();

    //공격!
    return Attack(OwnerComp);
}

EBTNodeResult::Type UBTTask_Attack::Attack(UBehaviorTreeComponent& OwnerComp)
{
    // AI의 위치 가져오기
    AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn();
    if (!OwnerActor) return EBTNodeResult::Failed;

    FVector ActorLocation = OwnerActor->GetActorLocation();

    UObject* DetectedPlayer = BlackboardComponent->GetValueAsObject(TEXT("DetectedPlayer"));
    if (IsValid(DetectedPlayer))
    {    
        // UObject를 AActor로 캐스팅
        AActor* PlayerActor = Cast<AActor>(DetectedPlayer);
        check(PlayerActor);

        ABasicWeapon* Weapon = Cast<ABasicWeapon>(WeaponComponent->GetChildActor());
        check(Weapon);

        FVector DirectionToPlayer = PlayerActor->GetActorLocation() - ActorLocation;
        DirectionToPlayer.Normalize();

        FRotator NewRotation = DirectionToPlayer.Rotation();
        OwnerActor->SetActorRotation(NewRotation);

        Weapon->SetAttackLoction(PlayerActor->GetActorLocation());
        Weapon->Attack();
        Weapon->ResetAttack();

        EBTNodeResult::InProgress;    
    }

    return EBTNodeResult::Succeeded;
}

void UBTTask_Attack::OnResult(EPathFollowingResult::Type MovementResult)
{
    if (!IsValid(Proxy))
    {
        return;
    }

    FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Succeeded);
}
