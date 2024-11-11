// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlayer.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABasicPlayer::ABasicPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(CollisionProfileName::Player);
	SpringArm = CreateDefaultSubobject<USoftWheelSpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Weapon = CreateDefaultSubobject<UWeaponChildActorComponent>(TEXT("Weapon"));
	{
		SpringArm->SetupAttachment(GetMesh());
		SpringArm->ProbeSize = 5.0;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritRoll = false;
		SpringArm->SetMinMaxTargetArmLength(SpringArm->GetMinTargetArmLength(), SpringArm->GetMaxTargetArmLength());
	}
	Camera->SetupAttachment(SpringArm);
	Weapon->SetupAttachment(GetMesh(), SocketName::Weapon);

	bUseControllerRotationYaw = false;

	const FRotator Rotation = FRotator(0., 90.0, 0.);
	const FVector Translation = FVector(0., 0., 90.0);
	FTransform SpringArmTransform = FTransform(Rotation, Translation, FVector::OneVector);
	SpringArm->SetRelativeTransform(SpringArmTransform);

	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));

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

// Called when the game starts or when spawned
void ABasicPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	SetFolderPath(FName("PawnOnly"));
}

void ABasicPlayer::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetData(DataTableRowHandle);
}

void ABasicPlayer::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FPawnTableRow* Data = DataTableRowHandle.GetRow<FPawnTableRow>(TEXT("Player"));
	if (!Data) { ensure(false); return; }

	CharacterData = Data;
	{
		UCharacterMovementComponent* Movement = GetCharacterMovement();
		Movement->bOrientRotationToMovement = true;
		Movement->GetNavAgentPropertiesRef().bCanCrouch = true;
		Movement->MaxWalkSpeed = CharacterData->MovementMaxSpeed;

		const float NewCapsuleHalfHeight = CharacterData->CollisionCapsuleHalfHeight * 0.5f;
		Movement->SetCrouchedHalfHeight(NewCapsuleHalfHeight);
	}
	{
		UCapsuleComponent* Capsule = GetCapsuleComponent();
		if (!FMath::IsNearlyEqual(Capsule->GetUnscaledCapsuleHalfHeight(), CharacterData->CollisionCapsuleHalfHeight))
		{
			Capsule->SetCapsuleHalfHeight(CharacterData->CollisionCapsuleHalfHeight, false);
		}
	}
	{
		USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
		SkeletalMeshComponent->SetSkeletalMesh(CharacterData->SkeletalMesh);
		SkeletalMeshComponent->SetRelativeTransform(CharacterData->MeshTransform);
		SkeletalMeshComponent->SetAnimClass(CharacterData->AnimClass);
	}

	{
		StatusComponent->SetStatus(CharacterData->Status);
	}
}

float ABasicPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (StatusComponent->IsDie()) { return 0.f; }

	float DamageResult = StatusComponent->TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (FMath::IsNearlyZero(DamageResult)) { return 0.0; }

	if (Controller)
	{
		Controller->StopMovement();
	}

	if (StatusComponent->IsDie() && !CharacterData->DieMontage.IsEmpty())
	{
		PlayerController = Cast<APlayerController>(Controller);
		if (PlayerController)
		{
			PlayerController->DisableInput(PlayerController);
		}
		SetActorEnableCollision(false);

		const int64 Index = FMath::RandRange(0, CharacterData->DieMontage.Num() - 1);
		CurrentDieMontage = CharacterData->DieMontage[Index];

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Play(CurrentDieMontage);
		UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnDie"),
			CharacterData->DieMontage[Index]->GetPlayLength() - 0.1f, false);
	}
	else if (!StatusComponent->IsDie() && !CharacterData->HitReactMontage.IsEmpty())
	{
		const int64 HitReactIndex = FMath::RandRange(0, CharacterData->HitReactMontage.Num() - 1);
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Play(CharacterData->HitReactMontage[HitReactIndex]);
	}

	return 0.0f;
}

void ABasicPlayer::OnPaperBurnEffect(float InDissolve)
{
	const int32 MaterialNum = MaterialInstanceDynamics.Num();
	for (int32 i = 0; i < MaterialNum; ++i)
	{
		MaterialInstanceDynamics[i]->SetScalarParameterValue(MF_PostEffect::PaperBurnDissolve, InDissolve);
	}
}

void ABasicPlayer::OnPaperBurnEffectEnd()
{
	Destroy();
}

void ABasicPlayer::OnDie()
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

void ABasicPlayer::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	RecalculateBaseEyeHeight();
	FVector& MeshRelativeLocation = GetMesh()->GetRelativeLocation_DirectMutable();
	MeshRelativeLocation.Z = CharacterData->MeshTransform.GetLocation().Z + HalfHeightAdjust;
	BaseTranslationOffset.Z = MeshRelativeLocation.Z;

	K2_OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
}

void ABasicPlayer::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	RecalculateBaseEyeHeight();

	FVector& MeshRelativeLocation = GetMesh()->GetRelativeLocation_DirectMutable();
	MeshRelativeLocation.Z = CharacterData->MeshTransform.GetLocation().Z;
	BaseTranslationOffset.Z = MeshRelativeLocation.Z;

	K2_OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
}

void ABasicPlayer::SetMoveSpeed(const bool IsRun)
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	if (Movement)
	{
		float MaxMoveSpeed = CharacterData->MovementMaxSpeed;

		if (IsRun)
		{
			MaxMoveSpeed = CharacterData->RunMaxSpeed;
		}

		Movement->MaxWalkSpeed = MaxMoveSpeed;
	}
}

void ABasicPlayer::FireProjectile(int32 InCount)
{
	StatusComponent->ProjectileFire(GetController(), InCount, 100);
}

void ABasicPlayer::SwitchWeaponAnim(EWeaponType NewWeapon)
{
	if (CurrentWeaponType == NewWeapon)
		return;

	CurrentWeaponType = NewWeapon;

	int32 WeaponIdx = GetWeaponAnimIdx(CurrentWeaponType);

	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	if (SkeletalMeshComponent)
	{
		if (CharacterData->WeaponAnimType.Num() < WeaponIdx)
		{
			UE_LOG(LogTemp, Error, TEXT("CharacterData->WeaponAnimType.Num() < WeaponIdx"));
			return;
		}


		SkeletalMeshComponent->SetAnimClass(CharacterData->WeaponAnimType[WeaponIdx]);
	}
}

int32 ABasicPlayer::GetWeaponAnimIdx(EWeaponType InWeapon)
{
	int32 AnimIndex = -1;

	switch (InWeapon)
	{
	case EWeaponType::WT_None:
		AnimIndex = 0;  // 기본 모션
		break;
	case EWeaponType::WT_Knife:
		AnimIndex = 1;  // 나이프 모션
		break;
	case EWeaponType::WT_Pistol:
		AnimIndex = 2;  // 피스톨 모션
		break;
	case EWeaponType::WT_Rifle:
		AnimIndex = 3;  // 라이플 모션
		break;
	case EWeaponType::WT_Grenade:
		AnimIndex = 4;  // 수류탄 모션
		break;
	default:
		break;
	}

	return AnimIndex;
}

// Called every frame
void ABasicPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABasicPlayer::GetMeleeDamage()
{
	float Damage = 0.0f;
	if (StatusComponent)
	{
		Damage = StatusComponent->GetCharacterStatus().MeleeAttackPoint;
	}

	return Damage;
}

