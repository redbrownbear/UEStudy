// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Enemy/BasicEnemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Utils.h"
#include "Actors/Enemy/BasicEnemyController.h"
#include "PaperSprite.h"


// Sets default values
ABasicEnemy::ABasicEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->SetCollisionProfileName(CollisionProfileName::Player);
	Weapon = CreateDefaultSubobject<UWeaponChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), SocketName::Weapon);
	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));

	// HP Bar
	{
		//ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprints'/Game/UI/UI_HPBar.UI_HPBar_C'"));
		//HPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidgetComponent"));
		//HPWidgetComponent->SetupAttachment(RootComponent);
		//HPWidgetComponent->SetRelativeLocation(FVector(0., 0., 130.0));
		//HPWidgetComponent->SetDrawSize(FVector2D(256.3, 17.0));
		//HPWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		//HPWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//HPWidgetComponent->SetWidgetClass(WidgetClass.Class);
	}

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfig_Sight->SightRadius = 800.f;
	AISenseConfig_Sight->LoseSightRadius = 1000.f;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 120.f;
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	{
		static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveAsset(TEXT("/Script/Engine.CurveFloat'/Game/Blueprints/Effect/CV_PaperBurn.CV_PaperBurn'"));
		check(CurveAsset.Object);
		PaperBurnEffectTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("PaperBurnEffectTimelineComponent"));

		FOnTimelineFloat Delegate;
		Delegate.BindDynamic(this, &ThisClass::OnPaperBurnEffect);
		PaperBurnEffectTimelineComponent->AddInterpFloat(CurveAsset.Object, Delegate);

		FOnTimelineEvent EndDelegate;
		EndDelegate.BindDynamic(this, &ThisClass::OnPaperBurnEffectEnd);
		PaperBurnEffectTimelineComponent->SetTimelineFinishedFunc(EndDelegate);
	}
}

void ABasicEnemy::SpawnData(const FDataTableRowHandle& InDataTableRowHandle, const FName& enemyName)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FPawnTableRow* Data = DataTableRowHandle.GetRow<FPawnTableRow>(enemyName.ToString());
	if (!Data) { ensure(false); return; }

	EnemyData = Data;
	{
		USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
		SkeletalMeshComponent->SetSkeletalMesh(Data->SkeletalMesh);
		SkeletalMeshComponent->SetRelativeTransform(Data->MeshTransform);
		SkeletalMeshComponent->SetAnimClass(Data->AnimClass);
	}
	{
		UCapsuleComponent* Capsule = GetCapsuleComponent();
		if (!FMath::IsNearlyEqual(Capsule->GetUnscaledCapsuleHalfHeight(), Data->CollisionCapsuleHalfHeight))
		{
			Capsule->SetCapsuleHalfHeight(Data->CollisionCapsuleHalfHeight, false);
		}
	}
	{
		UCharacterMovementComponent* Movement = GetCharacterMovement();
		Movement->bOrientRotationToMovement = true;
		Movement->GetNavAgentPropertiesRef().bCanCrouch = true;
		Movement->MaxWalkSpeed = Data->MovementMaxSpeed;

		const float NewCapsuleHalfHeight = Data->CollisionCapsuleHalfHeight * 0.5f;
		Movement->SetCrouchedHalfHeight(NewCapsuleHalfHeight);
	}
	{
		AIControllerClass = EnemyData->AIControllerClass;
		Weapon->SetData(EnemyData->Weapon);
	}
}

void ABasicEnemy::InitPathFinder()
{
	PathFinderRef = Cast<APathFinder>(UGameplayStatics::GetActorOfClass(GetWorld(), APathFinder::StaticClass()));

	if (PathFinderRef)
	{
		if (ABasicEnemyController* BasicEnemyController = Cast<ABasicEnemyController>(Controller))
		{
			BasicEnemyController->SetPatrolPath(PathFinderRef->GetPath());
		}
	}
}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();

	SetFolderPath(FName("PawnOnly"));

	//UUserWidgetBase* UserWidget = Cast<UUserWidgetBase>(HPWidgetComponent->GetWidget());
	//check(UserWidget);
	//UserWidget->SetOwningPawn(this);
}


void ABasicEnemy::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetActorTransform(Transform);
}

float ABasicEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (StatusComponent->IsDie()) { return 0.f; }

	float DamageResult = StatusComponent->TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (FMath::IsNearlyZero(DamageResult)) { return 0.0; }

	if (Controller)
	{
		Controller->StopMovement();
	}

	if (StatusComponent->IsDie() && !EnemyData->DieMontage.IsEmpty())
	{
		if (Controller)
		{
			Controller->Destroy();
		}
		SetActorEnableCollision(false);

		const int64 Index = FMath::RandRange(0, EnemyData->DieMontage.Num() - 1);
		CurrentDieMontage = EnemyData->DieMontage[Index];

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Play(CurrentDieMontage);
		UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnDie"),
			EnemyData->DieMontage[Index]->GetPlayLength() - 0.1f, false);
	}
	else if (!StatusComponent->IsDie() && !EnemyData->HitReactMontage.IsEmpty())
	{
		const int64 HitReactIndex = FMath::RandRange(0, EnemyData->HitReactMontage.Num() - 1);
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Play(EnemyData->HitReactMontage[HitReactIndex]);
	}

	return 0.0f;
}

void ABasicEnemy::OnPaperBurnEffect(float InDissolve)
{
	const int32 MaterialNum = MaterialInstanceDynamics.Num();
	for (int32 i = 0; i < MaterialNum; ++i)
	{
		MaterialInstanceDynamics[i]->SetScalarParameterValue(MF_PostEffect::PaperBurnDissolve, InDissolve);
	}
}

void ABasicEnemy::OnPaperBurnEffectEnd()
{
	Destroy();
}

void ABasicEnemy::OnDie()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Pause(CurrentDieMontage);

	const int32 MaterialNum = GetMesh()->GetSkinnedAsset()->GetMaterials().Num();
	MaterialInstanceDynamics.Reserve(MaterialNum);
	for (int32 i = 0; i < MaterialNum; ++i)
	{
		MaterialInstanceDynamics.Add(GetMesh()->CreateDynamicMaterialInstance(i));
	}

	PaperBurnEffectTimelineComponent->Play();
}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
