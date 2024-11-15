// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_PathTrace.h"
#include "Components/SplineComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/AIAsyncTaskBlueprintProxy.h"

UBTTask_PathTrace::UBTTask_PathTrace()
{
	NodeName = "PathTrace";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_PathTrace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();
	SplineComponent = Cast<USplineComponent>(BlackboardComponent->GetValueAsObject(TEXT("SplineComponent")));
	check(SplineComponent);

	SplinePoints = SplineComponent->GetNumberOfSplinePoints();
	const int32 Index = FMath::RandRange(0, SplinePoints - 1);
	const FVector TargetLocation = SplineComponent->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);

	APawn* Pawn = AIOwner->GetPawn();
	Proxy = UAIBlueprintHelperLibrary::CreateMoveToProxyObject(this, Pawn, TargetLocation);
	Proxy->OnSuccess.AddDynamic(this, &ThisClass::OnResult);
	Proxy->OnFail.AddDynamic(this, &ThisClass::OnResult);

	return EBTNodeResult::InProgress;
}

void UBTTask_PathTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	UObject* DetectedPlayer = BlackboardComponent->GetValueAsObject(TEXT("DetectedPlayer"));
	if (IsValid(DetectedPlayer))
	{
		AIOwner->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}

void UBTTask_PathTrace::OnResult(EPathFollowingResult::Type MovementResult)
{
	if (!IsValid(Proxy))
	{
		return;
	}
	if (MovementResult == EPathFollowingResult::Success)
	{
		const int32 Index = FMath::RandRange(0, SplinePoints - 1);
		BlackboardComponent->SetValueAsInt(TEXT("PatrolIndex"), Index);
	}

	FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Succeeded);
}
