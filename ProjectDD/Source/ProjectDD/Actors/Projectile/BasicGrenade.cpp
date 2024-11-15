// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectile/BasicGrenade.h"
#include "Misc/Utils.h"
#include "Actors/Enemy/BasicEnemy.h"
#include "Actors/Player/BasicPlayer.h"

// Sets default values
ABasicGrenade::ABasicGrenade()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	StaticMeshComponent->SetCollisionProfileName(CollisionProfileName::Projectile);

}

void ABasicGrenade::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FProjectileTableRow* Data = DataTableRowHandle.GetRow<FProjectileTableRow>(TEXT("Projectile"));
	if (!Data) { ensure(false); return; }

	ProjectileData = Data;
	InitialLifeSpan = Data->LifeSpan;

	ProjectileMovementComponent->InitialSpeed = Data->MaxSpeed;
	ProjectileMovementComponent->MaxSpeed = Data->MaxSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = Data->GravityScale;

	StaticMeshComponent->SetStaticMesh(Data->StaticMesh);
	StaticMeshComponent->SetRelativeTransform(Data->Transform);

	StaticMeshComponent->SetCollisionProfileName(CollisionProfileName::Grenade);

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
}

