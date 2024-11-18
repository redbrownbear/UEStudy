// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Enemy/BasicEnemyController.h"
#include "GameFramework/Character.h"
#include "Components/StatusComponent.h"
#include "Kismet/KismetSystemLibrary.h"
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

	ABasicEnemy* OwningEnemy = Cast<ABasicEnemy>(GetPawn());

	// Montage가 Play 중이라면 BT 내부에서 AI 진행을 멈춘다
	const bool bMontagePlaying = OwningPawn->GetComponentByClass<USkeletalMeshComponent>()->GetAnimInstance()->IsAnyMontagePlaying();

	Blackboard->SetValueAsBool(TEXT("MontagePlaying"), bMontagePlaying);

	FindPlayerByPerception();
}

void ABasicEnemyController::OnDamaged(float CurrentHP, float MaxHP)
{
	AController* Instigator_ = StatusComponentRef->GetLastInstigator();
	APawn* InstigatorPawn = Instigator_->GetPawn();

	if (!InstigatorPawn)
		return;

	bDamaged = true;

	ABasicEnemy* OwningEnemy = Cast<ABasicEnemy>(GetPawn());
	if (OwningEnemy->GetWeaponType() == EWeaponType::WT_Knife || OwningEnemy->GetWeaponType() == EWeaponType::WT_Grenade)
	{
		Blackboard->SetValueAsObject(TEXT("DetectedPlayer"), Cast<UObject>(InstigatorPawn));
		return;
	}
		
	//자기들 끼리 공격하기
	Blackboard->ClearValue(TEXT("AttackRangePlayer"));
	Blackboard->SetValueAsObject(TEXT("AttackRangePlayer"), Cast<UObject>(InstigatorPawn));
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("ResetOnDamaged"), 5.0f, false);
}

void ABasicEnemyController::ResetOnDamaged()
{
	bDamaged = false;
}

void ABasicEnemyController::FindEnemyByPerception(AActor* InNearbyEnemy)
{
	if (!Blackboard)
		return;

	if (InNearbyEnemy)
	{
		Blackboard->SetValueAsObject(TEXT("CheckEnemy"), Cast<UObject>(InNearbyEnemy));
	}
}

void ABasicEnemyController::EraseEnemyByPerception(AActor* InNearbyEnemy)
{
	if (!Blackboard)
		return;
	if (InNearbyEnemy)
	{
		Blackboard->ClearValue(TEXT("CheckEnemy"));
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
				if (!DetectedPlayer || !OwningPawn) return;

				FVector PlayerLocation = DetectedPlayer->GetActorLocation();
				FVector EnemyLocation = OwningPawn->GetActorLocation();
				float Distance = FVector::Dist(PlayerLocation, EnemyLocation);

				ABasicEnemy* OwningEnemy = Cast<ABasicEnemy>(GetPawn());
				if (!OwningEnemy) return;

				SwitchAttackDetect(DetectedPlayer, OwningEnemy->GetWeaponType(), Distance);

				bFound = true;
			}
		}
		if (!bFound)
		{
			Blackboard->ClearValue(TEXT("DetectedPlayer"));
			Blackboard->ClearValue(TEXT("AttackRangePlayer"));
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

void ABasicEnemyController::SwitchAttackDetect(AMainPlayer* DetectedPlayer, EWeaponType InWeaponType, float InDistance)
{
	bool isAttack = bDamaged;

	switch (InWeaponType)
	{
	case EWeaponType::WT_Knife:
		if (InDistance <= 100.0f)
		{
			Blackboard->SetValueAsObject(TEXT("AttackRangePlayer"), DetectedPlayer);
			Blackboard->ClearValue(TEXT("DetectedPlayer"));
			isAttack = true;
		}
		break;
	case EWeaponType::WT_Pistol:
	case EWeaponType::WT_Rifle:
		if (InDistance <= 2000.0f)
		{
			Blackboard->SetValueAsObject(TEXT("AttackRangePlayer"), DetectedPlayer);
			Blackboard->ClearValue(TEXT("DetectedPlayer"));
			isAttack = true;
		}
		break;
	case EWeaponType::WT_Grenade:
		if (InDistance <= 1300.0f)
		{
			Blackboard->SetValueAsObject(TEXT("AttackRangePlayer"), DetectedPlayer);
			Blackboard->ClearValue(TEXT("DetectedPlayer"));
			isAttack = true;
		}
		break;
	default:
		break;
	}

	if(!isAttack)
		Blackboard->ClearValue(TEXT("AttackRangePlayer"));
		Blackboard->SetValueAsObject(TEXT("DetectedPlayer"), DetectedPlayer);
}
