// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusComponent.h"
#include "Actors/Player/BasicPlayer.h"

#include "SubSystem/HUDManagerSubsystem.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UStatusComponent::SetStatus(FDataTableRowHandle InDataTableRowHandle)
{
	if (InDataTableRowHandle.IsNull()) { return; }
	FPawnStatusTableRow* Data = InDataTableRowHandle.GetRow<FPawnStatusTableRow>(TEXT("Status"));
	if (!Data) { ensure(false); return; }

	UHUDManagerSubsystem* HUDManager = GetWorld()->GetGameInstance()->GetSubsystem<UHUDManagerSubsystem>();
	if (!HUDManager)
	{
		check(false);
		return;
	}

	FPawnStatusTableRow Status;

	Status.HP = Data->HP;
	Status.MAXHP = Data->MAXHP;
	Status.ARMOR = Data->ARMOR;
	Status.MAXARMOR = Data->MAXARMOR;
	Status.MeleeAttackPoint = Data->MeleeAttackPoint;
	Status.BulletCount9mm = Data->BulletCount9mm;
	Status.MaxBulletCount9mm = Data->MaxBulletCount9mm;
	Status.BulletCount556mm = Data->BulletCount556mm;
	Status.MaxBulletCount556mm = Data->MaxBulletCount556mm;
	Status.GrenadeCount = Data->GrenadeCount;
	Status.MaxGrenadeCount = Data->MaxGrenadeCount;

	CharacterStatus = Status;

	if(IsPlayer())
		HUDManager->SetStatus(CharacterStatus);
}

void UStatusComponent::SetUI()
{
	UHUDManagerSubsystem* HUDManager = GetWorld()->GetGameInstance()->GetSubsystem<UHUDManagerSubsystem>();
	if (!HUDManager)
	{
		check(false);
		return;
	}

	if (IsPlayer())
	{
		HUDManager->SetStatus(CharacterStatus);
		HUDManager->DrawStatusUI();
	}
}

// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UStatusComponent::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bDie)
		return 0.f;

	if (FMath::IsNearlyZero(Damage)) { return 0.0; }

	float NewDamage = Damage;

	NewDamage = FMath::Clamp(NewDamage, 0.f, NewDamage);
	CharacterStatus.HP -= NewDamage;

	if (CharacterStatus.HP <= 0.f)
	{
		CharacterStatus.HP = 0;
		SetDie(true);
	}
		
	SetUI();
	{
		LastInstigator = EventInstigator;
		OnHPChanged.Broadcast(CharacterStatus.HP, CharacterStatus.MAXHP);
		if (CharacterStatus.HP <= 0.f)
		{
			OnDie.Broadcast();
		}
	}

	return NewDamage;
}

void UStatusComponent::ProjectileFire(AController* EventInstigator, EWeaponType InWeaponType, int32 BulletCount)
{
	UHUDManagerSubsystem* HUDManager = GetWorld()->GetGameInstance()->GetSubsystem<UHUDManagerSubsystem>();
	if (!HUDManager)
	{
		check(false);
		return;
	}
	if (InWeaponType == EWeaponType::WT_Rifle)
	{
		CharacterStatus.BulletCount556mm -= BulletCount;
	}
	else if (InWeaponType == EWeaponType::WT_Pistol)
	{
		CharacterStatus.BulletCount9mm -= BulletCount;
	}

	SetUI();
}


bool UStatusComponent::IsPlayer()
{
	ABasicPlayer* Player = Cast<ABasicPlayer>(GetOwner());
	if (Player)
		return true;

	return false;
}

