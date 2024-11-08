// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_Projectile.h"
#include "Actors/Projectile/BasicProjectile.h"
#include "Actors/Weapon/BasicWeapon.h"
#include "Components/WeaponChildActorComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Data//WeaponData.h"

#include "Misc/Utils.h"


UAnimNotify_Projectile::UAnimNotify_Projectile()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(90, 90, 200, 255);
#endif // WITH_EDITORONLY_DATA
}

FRotator UAnimNotify_Projectile::GetPlayerProjectileRotation(const FVector& InProjectSpawnLocation, const FVector& InEndLocation)
{
	FRotator Rotator;
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, InProjectSpawnLocation, InEndLocation, ECC_Visibility);

	if (HitResult.bBlockingHit)
	{
		Rotator = UKismetMathLibrary::FindLookAtRotation(InProjectSpawnLocation, HitResult.ImpactPoint);
	}
	else
	{
		Rotator = UKismetMathLibrary::FindLookAtRotation(InProjectSpawnLocation, InEndLocation);
	}

	return Rotator;
}

void UAnimNotify_Projectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
#if WITH_EDITOR
	if (GIsEditor && MeshComp->GetWorld() != GWorld) { return; } // 에디터 프리뷰
#endif

	APawn* OwningPawn = Cast<APawn>(MeshComp->GetOwner());
	check(OwningPawn);

	UWeaponChildActorComponent* WeaponChildActorComponent = OwningPawn->GetComponentByClass<UWeaponChildActorComponent>();
	check(WeaponChildActorComponent);
	AActor* BaseActor = WeaponChildActorComponent->GetChildActor();
	check(BaseActor);

	ABasicWeapon* WeaponActor = Cast<ABasicWeapon>(BaseActor);
	check(WeaponActor);

	USkeletalMeshComponent* WeaponSkeletalMeshComponent = WeaponActor->GetComponentByClass<USkeletalMeshComponent>();
	check(WeaponSkeletalMeshComponent);

	const FTransform MuzzleTransform = WeaponSkeletalMeshComponent->GetSocketTransform(SocketName::Muzzle);
#if WITH_EDITOR
	USkeletalMeshSocket const* SkeletalMeshSocket = WeaponSkeletalMeshComponent->GetSocketByName(SocketName::Muzzle);
	check(SkeletalMeshSocket);
#endif

	FVector StartLocation = MuzzleTransform.GetLocation();
	FVector EndLocation = StartLocation + (MuzzleTransform.GetRotation().Vector() * 10000.0f);

	FRotator ProjectileRotator = FRotator::ZeroRotator;
	ProjectileRotator = GetPlayerProjectileRotation(StartLocation, EndLocation);

	const FWeaponTableRow* WeaponTableRow = WeaponActor->GetWeaponTableRow();
	const FProjectileTableRow* ProjectileTableRow = WeaponTableRow->ProjectileRowHandle.GetRow<FProjectileTableRow>(TEXT("Projectile"));
	check(ProjectileTableRow);

	UWorld* World = OwningPawn->GetWorld();
	ABasicProjectile* Projectile = World->SpawnActorDeferred<ABasicProjectile>(ProjectileTableRow->ProjectileClass,
		FTransform::Identity, OwningPawn, OwningPawn, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Projectile->SetData(WeaponTableRow->ProjectileRowHandle);

	FTransform NewTransform;
	NewTransform.SetLocation(StartLocation);
	NewTransform.SetRotation(ProjectileRotator.Quaternion());

	Projectile->FinishSpawning(NewTransform);
	Projectile->SetActorRotation(ProjectileRotator.Quaternion() * FQuat(FRotator(0.0f, -90.0f, 0.0f)));
	
	Projectile->ProjectileFire(OwningPawn, 1);//한발씩 소모
}
