// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/BasicWeapon.h"
#include "Actors/PlayerController/BasicPlayerController.h"

// Sets default values
ABasicWeapon::ABasicWeapon()
  : OwningPawn(nullptr),
    BasicAnimInstance(nullptr),
    OwnerStatusComponent(nullptr),
    WeaponTableRow(nullptr),
	DefaultSceneRoot(nullptr),
	SkeletalMeshComponent(nullptr),
	ParticleSystemComponent(nullptr)

{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(RootComponent);

	// Input
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprints/Input/Weapon/IMC_Weapon.IMC_Weapon'") };
		check(Asset.Object);

		IMC_Weapon = Asset.Object;
	}
}

void ABasicWeapon::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;

	if (DataTableRowHandle.IsNull()) { return; }
	FWeaponTableRow* Data = DataTableRowHandle.GetRow<FWeaponTableRow>(TEXT("Weapon"));
	if (!Data) { ensure(false); return; }
	WeaponTableRow = Data;

	SkeletalMeshComponent->SetSkeletalMesh(Data->SkeletalMesh);
	SkeletalMeshComponent->SetRelativeTransform(Data->Transform);
	check(Data->AnimClass);
	USkeletalMeshComponent* MeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
	check(MeshComponent);
	MeshComponent->SetAnimClass(Data->AnimClass);

	// Owner 정보 세팅
	if(OwningPawn == nullptr)
	{
		OwningPawn = Cast<APawn>(GetOwner());
		check(OwningPawn);
		BasicAnimInstance = Cast<UBaisicCharacterAnimInstance>(MeshComponent->GetAnimInstance());
		check(BasicAnimInstance);
		OwnerStatusComponent = OwningPawn->GetComponentByClass<UStatusComponent>();
		check(OwnerStatusComponent);
		{
			BasicAnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnMontageEnd);
		}

		if (OwningPawn->IsA(ABasicPlayer::StaticClass()))
		{
			SpringArm = OwningPawn->GetComponentByClass<USoftWheelSpringArmComponent>();
			check(SpringArm);
		}

	}

	if(Data->WeaponType == EWeaponType::WT_Knife || Data->WeaponType == EWeaponType::WT_Grenade)
	{
		OwnerStatusComponent->SetAim(true);
	}

	// Input
	{
		if (APlayerController* PC = Cast<APlayerController>(OwningPawn->GetController()))
		{
			UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
			if (!Subsystem->HasMappingContext(IMC_Weapon))
			{
				Subsystem->AddMappingContext(IMC_Weapon, 0);
			}

			if (!InputComponent)
			{
				EnableInput(PC);
				UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
				ensure(EnhancedInputComponent);
				if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Weapon, TEXT("IA_Attack")))
				{
					EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnFire);
					EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::OnResetFire);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("IA_Attack is disabled"));
				}

				if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Weapon, TEXT("IA_Aim")))
				{
					EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnAim);
					EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::EndAim);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("IA_Aim is disabled"));
				}
			}
		}
	}
}

void ABasicWeapon::OnFire(const FInputActionValue& InputActionValue)
{
	if (!OwnerStatusComponent->IsAim())
		return;

	EndMotion();
	Attack();	
}

void ABasicWeapon::OnResetFire(const FInputActionValue& InputActionValue)
{
	ResetAttack();
}

void ABasicWeapon::EndMotion()
{
	if (ABasicPlayerController* PC = Cast<ABasicPlayerController>(OwningPawn->GetController()))
	{
		PC->CrouchOver();
		PC->RunOver();
	}
}

void ABasicWeapon::Attack()
{
	if (bCanfire == false)
		return;

	if (WeaponTableRow->WeaponAttackMontage)
	{
		// 모든 몽타주가 재생 중이지 않을 때
		if (!BasicAnimInstance->Montage_IsPlaying(nullptr))
		{
			BasicAnimInstance->Montage_Play(WeaponTableRow->WeaponAttackMontage);
			bCanfire = false;
		}
	}
}

void ABasicWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void ABasicWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasicWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
