// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_Grenade.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/WeaponChildActorComponent.h"

#include "Actors/Projectile/BasicGrenade.h"
#include "Actors/Weapon/BasicWeapon.h"
#include "Data/ProjectileData.h"


void UAnimNotify_Grenade::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    APawn* OwningPawn = Cast<APawn>(MeshComp->GetOwner());
    check(OwningPawn);

    UWeaponChildActorComponent* WeaponChildActorComponent = OwningPawn->GetComponentByClass<UWeaponChildActorComponent>();
    check(WeaponChildActorComponent);

    AActor* BaseActor = WeaponChildActorComponent->GetChildActor();
    check(BaseActor);

    ABasicWeapon* WeaponActor = Cast<ABasicWeapon>(BaseActor);
    check(WeaponActor);

    const FWeaponTableRow* WeaponTableRow = WeaponActor->GetWeaponTableRow();
    const FProjectileTableRow* ProjectileTableRow = WeaponTableRow->ProjectileRowHandle.GetRow<FProjectileTableRow>(TEXT("Projectile"));
    check(ProjectileTableRow);

    UWorld* World = OwningPawn->GetWorld();
    ABasicGrenade* Grenade = World->SpawnActorDeferred<ABasicGrenade>(ProjectileTableRow->GrenadeClass,
        FTransform::Identity, OwningPawn, OwningPawn, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

    Grenade->SetData(WeaponTableRow->ProjectileRowHandle);
    FVector SpawnLocation = MeshComp->GetSocketLocation(SocketName::Weapon);
    FRotator SpawnRotation = MeshComp->GetSocketRotation(SocketName::Weapon);

    UProjectileMovementComponent* ProjectileMovement = Grenade->FindComponentByClass<UProjectileMovementComponent>();
    if (ProjectileMovement)
    {
        ProjectileMovement->SetVelocityInLocalSpace(ProjectileMovement->Velocity);
    }

    FTransform NewTransform;
    NewTransform.SetLocation(SpawnLocation);
    NewTransform.SetRotation(SpawnRotation.Quaternion());

    Grenade->FinishSpawning(NewTransform);
    Grenade->ProjectileFire(OwningPawn, WeaponActor->GetWeaponType(), 1);//한발씩 소모

}
