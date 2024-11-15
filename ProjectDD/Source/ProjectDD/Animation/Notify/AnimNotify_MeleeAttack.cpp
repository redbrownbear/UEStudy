// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_MeleeAttack.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Utils.h"

#include "Actors/Enemy/BasicEnemy.h"
#include "Actors/Player/BasicPlayer.h"

UAnimNotify_MeleeAttack::UAnimNotify_MeleeAttack()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(255, 255, 0, 255);
#endif // WITH_EDITORONLY_DATA
}

void UAnimNotify_MeleeAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	const FVector WeaponSocketLocation = MeshComp->GetSocketLocation(SocketName::Weapon);

	AActor* OwningActor = MeshComp->GetOwner();
#if WITH_EDITOR
	if (GIsEditor && OwningActor && OwningActor->GetWorld() != GWorld) { return; } // 에디터 프리뷰
#endif
	APawn* OwningPawn = Cast<APawn>(OwningActor);
	check(OwningPawn);
	ABasicEnemy* Enemy = Cast<ABasicEnemy>(OwningPawn);
	check(Enemy);
	ABasicPlayer* Player = Cast<ABasicPlayer>(OwningPawn);
	check(Player);

	const FName ProfileName = Enemy ? CollisionProfileName::Enemy : CollisionProfileName::Player;

	const float Damage = Enemy ? Enemy->GetMeleeDamage() : Player->GetMeleeDamage();

	TArray<AActor*> IgnoreActors;
	FHitResult HitResult;
	if (UKismetSystemLibrary::SphereTraceSingleByProfile(MeshComp,
		WeaponSocketLocation, WeaponSocketLocation, 100.f,
		ProfileName, false, IgnoreActors, EDrawDebugTrace::None,
		HitResult, true))
	{
		AActor* DamagedActor = HitResult.GetActor();
		UGameplayStatics::ApplyDamage(DamagedActor, Damage, OwningPawn->GetController(),
			OwningPawn, nullptr);
	}
}
