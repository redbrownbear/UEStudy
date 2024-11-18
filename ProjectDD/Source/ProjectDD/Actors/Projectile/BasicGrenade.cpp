// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectile/BasicGrenade.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Utils.h"
#include "Actors/Enemy/BasicEnemy.h"
#include "Actors/Player/BasicPlayer.h"
#include "SubSystem/ActorPoolSubsystem.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ABasicGrenade::ABasicGrenade()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

void ABasicGrenade::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FProjectileTableRow* Data = DataTableRowHandle.GetRow<FProjectileTableRow>(TEXT("Projectile"));
	if (!Data) { ensure(false); return; }

	ProjectileData = Data;
	InitialLifeSpan = Data->LifeSpan;
	ExplosionRadius = Data->ExplosionRadius;
	ExplosionDamage = Data->ExplosionDamage;
	FuseTime = Data->FuseTime;

	ProjectileMovementComponent->InitialSpeed = Data->MaxSpeed;
	ProjectileMovementComponent->MaxSpeed = Data->MaxSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = Data->GravityScale;

	StaticMeshComponent->SetStaticMesh(Data->StaticMesh);
	StaticMeshComponent->SetRelativeTransform(Data->Transform);

	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	StaticMeshComponent->SetCollisionProfileName(CollisionProfileName::Grenade);

	StaticMeshComponent->SetLinearDamping(1.0f);
	StaticMeshComponent->SetAngularDamping(1.0f);

	StaticMeshComponent->MoveIgnoreActors.Empty();
	StaticMeshComponent->MoveIgnoreActors.Add(GetOwner());
}

void ABasicGrenade::ProjectileFire(APawn* InOwner, EWeaponType InWeaponType, int32 InCount)
{
	ABasicEnemy* Enemy = Cast<ABasicEnemy>(InOwner);
	if (Enemy)
	{
		Enemy->FireProjectile(InWeaponType, InCount);
	}

	ABasicPlayer* Player = Cast<ABasicPlayer>(InOwner);
	if (Player)
	{
		Player->FireProjectile(InWeaponType, InCount);
	}

	GetWorld()->GetTimerManager().SetTimer(FuseTimerHandle, this, &ABasicGrenade::OnExplode, FuseTime);
}

// Called when the game starts or when spawned
void ABasicGrenade::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicGrenade::OnExplode()
{
	// 폭발 데미지 처리
	UGameplayStatics::ApplyRadialDamage(
		this,
		ExplosionDamage,
		GetActorLocation(),
		ExplosionRadius,
		UDamageType::StaticClass(),
		TArray<AActor*>(),
		this,
		GetInstigatorController(),
		true
	);

	FTransform NewTransform;
	NewTransform.SetLocation(GetActorLocation());
	NewTransform.SetRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	GetWorld()->GetSubsystem<UActorPoolSubsystem>()->SpawnHitEffectWithDecal(NewTransform, ProjectileData->HitEffectTableRowHandle);

	GetWorld()->GetTimerManager().SetTimer(ExplosionTimerHandle, this, &ABasicGrenade::OnExplosionFinished, 0.5f, false);
	GetWorld()->GetTimerManager().ClearTimer(FuseTimerHandle);
}

void ABasicGrenade::OnExplosionFinished()
{
	StaticMeshComponent->SetSimulatePhysics(false);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetVisibility(false);

	GetWorld()->GetTimerManager().ClearTimer(ExplosionTimerHandle);
}

