// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectile/BasicProjectile.h"
#include "Misc/Utils.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/ActorPoolSubsystem.h"

// Sets default values
ABasicProjectile::ABasicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	StaticMeshComponent->SetCollisionProfileName(CollisionProfileName::Projectile);
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

void ABasicProjectile::SetData(const FDataTableRowHandle& InDataTableRowHandle)
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

	StaticMeshComponent->MoveIgnoreActors.Empty();
	StaticMeshComponent->MoveIgnoreActors.Add(GetOwner());
}

// Called when the game starts or when spawned
void ABasicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasicProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector Location = GetActorLocation();
	if (!IsValid(this)) { return; }
	// BeginPlay 시점에 Overlapped 되면 들어 옴
	if (!bFromSweep)
	{
		Destroy();
		check(false);
		return;
	}

	FTransform NewTransform;
	NewTransform.SetLocation(SweepResult.ImpactPoint);
	FRotator Rotation = UKismetMathLibrary::Conv_VectorToRotator(SweepResult.ImpactNormal);
	NewTransform.SetRotation(Rotation.Quaternion());
	GetWorld()->GetSubsystem<UActorPoolSubsystem>()->SpawnHitEffectWithDecal(NewTransform, ProjectileData->HitEffectTableRowHandle);

	Destroy();

	UGameplayStatics::ApplyDamage(OtherActor, 1.f, GetInstigator()->GetController(), this, nullptr);
}

// Called every frame
void ABasicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

