// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Enemy/BasicEnemyController.h"
#include "GameFramework/Character.h"
#include "Components/StatusComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Actors/Player/MainPlayer.h"
#include "Actors/Enemy/BasicEnemy.h"

void ABasicEnemyController::BeginPlay()
{
	Super::BeginPlay();
	SetFolderPath(FName("ControllerOnly"));
}

void ABasicEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	StatusComponentRef = InPawn->GetComponentByClass<UStatusComponent>();
	StatusComponentRef->OnHPChanged.AddDynamic(this, &ThisClass::OnDamaged);
}

void ABasicEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PathFinder)
		return;

	APawn* OwningPawn = GetPawn();

	// Montage가 Play 중이라면 BT 내부에서 AI 진행을 멈춘다
	const bool bMontagePlaying = OwningPawn->GetComponentByClass<USkeletalMeshComponent>()->GetAnimInstance()->IsAnyMontagePlaying();

	Blackboard->SetValueAsBool(TEXT("MontagePlaying"), bMontagePlaying);

	if (!bDamaged)
	{
		FindEnemyByPerception();
		FindPlayerByPerception();
	}

}

void ABasicEnemyController::OnDamaged(float CurrentHP, float MaxHP)
{
	bDamaged = true;
	AController* Instigator_ = StatusComponentRef->GetLastInstigator();
	APawn* InstigatorPawn = Instigator_->GetPawn();
	check(InstigatorPawn);
	Blackboard->SetValueAsObject(TEXT("DetectedPlayer"), Cast<UObject>(InstigatorPawn));
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("ResetOnDamaged"), 10.f, false);
}

void ABasicEnemyController::ResetOnDamaged()
{
	bDamaged = false;
}

void ABasicEnemyController::FindEnemyByPerception()
{
	APawn* OwningPawn = GetPawn();
	if (UAIPerceptionComponent* AIPerceptionComponent = OwningPawn->GetComponentByClass<UAIPerceptionComponent>())
	{
		TArray<AActor*> OutActors;
		AIPerceptionComponent->GetCurrentlyPerceivedActors(UAISenseConfig_Sight::StaticClass(), OutActors);

		bool bFound = false;
		for (AActor* It : OutActors)
		{
			if (ABasicEnemy* DetectedEnemy = Cast<ABasicEnemy>(It))
			{
				bFound = true;
				Blackboard->SetValueAsObject(TEXT("CheckEnemy"), Cast<UObject>(DetectedEnemy));
				break;
			}
		}
		if (!bFound)
		{
			Blackboard->ClearValue(TEXT("CheckEnemy"));
		}
	}
}

void ABasicEnemyController::FindPlayerByPerception()
{
	APawn* OwningPawn = GetPawn();
	if (UAIPerceptionComponent* AIPerceptionComponent = OwningPawn->GetComponentByClass<UAIPerceptionComponent>())
	{
		TArray<AActor*> OutActors;
		AIPerceptionComponent->GetCurrentlyPerceivedActors(UAISenseConfig_Sight::StaticClass(), OutActors);

		bool bFound = false;
		for (AActor* It : OutActors)
		{
			if (AMainPlayer* DetectedPlayer = Cast<AMainPlayer>(It))
			{
				bFound = true;
				Blackboard->SetValueAsObject(TEXT("DetectedPlayer"), Cast<UObject>(DetectedPlayer));
				break;
			}
		}
		if (!bFound)
		{
			Blackboard->ClearValue(TEXT("DetectedPlayer"));
		}
	}
}

void ABasicEnemyController::SetPatrolPath(TObjectPtr<USplineComponent> NewPathFinder)
{
	PathFinder = NewPathFinder;
	if (!IsValid(PathFinder))
	{
		checkf(false, TEXT("PatrolPath not valid"));
		return;
	}

	if (!IsValid(BrainComponent))
	{
		UBehaviorTree* BehaviorTree = LoadObject<UBehaviorTree>(nullptr, TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprints/Enemy/AI/BT_BasicEnemy.BT_BasicEnemy'"));
		check(BehaviorTree);
		RunBehaviorTree(BehaviorTree);
	}

	Blackboard->SetValueAsObject(TEXT("SplineComponent"), PathFinder);	
}
