// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_Grenade.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/WeaponChildActorComponent.h"

#include "Actors/Projectile/BasicGrenade.h"
#include "Actors/Weapon/BasicWeapon.h"
#include "Data/ProjectileData.h"
#include "Actors/Enemy/BasicEnemy.h"


void UAnimNotify_Grenade::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    APawn* OwningPawn = Cast<APawn>(MeshComp->GetOwner());
    if (!OwningPawn)
    {
        check(OwningPawn);
        return;
    }
    AController* Controller = OwningPawn->GetController();
    if (!Controller)
    {
        check(Controller);
        return;
    }

    UWeaponChildActorComponent* WeaponChildActorComponent = OwningPawn->GetComponentByClass<UWeaponChildActorComponent>();
    check(WeaponChildActorComponent);

    AActor* BaseActor = WeaponChildActorComponent->GetChildActor();
    check(BaseActor);

    ABasicWeapon* WeaponActor = Cast<ABasicWeapon>(BaseActor);
    check(WeaponActor);

    const FWeaponTableRow* WeaponTableRow = WeaponActor->GetWeaponTableRow();
    const FProjectileTableRow* ProjectileTableRow = WeaponTableRow->ProjectileRowHandle.GetRow<FProjectileTableRow>(TEXT("Projectile"));
    check(ProjectileTableRow);

    FRotator ControlRotation = Controller->GetControlRotation();
    FVector ThrowDirection = ControlRotation.Vector();

    FVector SpawnLocation = MeshComp->GetSocketLocation(SocketName::Weapon);

    //AI 전용
    if (ABasicEnemy* BasicEnemy = Cast<ABasicEnemy>(OwningPawn))
    {
        const float AngleDegrees = 30.0f; 
        const float AngleRadians = FMath::DegreesToRadians(AngleDegrees);

        FVector UpwardDirection = FVector(0.0f, 0.0f, FMath::Tan(AngleRadians));
        ThrowDirection = (ThrowDirection + UpwardDirection).GetSafeNormal();
    }

    FVector LaunchVelocity = ThrowDirection * ProjectileTableRow->MaxSpeed;

    UWorld* World = OwningPawn->GetWorld();
    ABasicGrenade* Grenade = World->SpawnActorDeferred<ABasicGrenade>(
        ProjectileTableRow->GrenadeClass, FTransform::Identity, OwningPawn, OwningPawn, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
    if (Grenade)
    {
        Grenade->SetData(WeaponTableRow->ProjectileRowHandle);

        FTransform NewTransform;
        NewTransform.SetLocation(SpawnLocation);
        NewTransform.SetRotation(ThrowDirection.Rotation().Quaternion());

        Grenade->FinishSpawning(NewTransform);

        // ProjectileMovementComponent를 사용해 초기 속도와 중력 설정
        UProjectileMovementComponent* ProjectileMovement = Grenade->FindComponentByClass<UProjectileMovementComponent>();
        if (ProjectileMovement)
        {
            ProjectileMovement->Velocity = LaunchVelocity;
        }

        // 수류탄 발사 처리
        Grenade->ProjectileFire(OwningPawn, WeaponActor->GetWeaponType(), 1); // 한발 소모
    }
}
