// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SplineComponent.h"

#include "Components/WeaponChildActorComponent.h"
#include "Components/StatusComponent.h"

#include "PaperSpriteComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "Animation/BaisicCharacterAnimInstance.h"

#include "Actors/Enemy/PathFinder.h"
#include "Data/PawnData.h"
#include "Enum/WeaponType.h"

#include "BasicEnemy.generated.h"


UCLASS()
class PROJECTDD_API ABasicEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicEnemy();

	void SpawnData(const FDataTableRowHandle& InDataTableRowHandle, const FName& enemyName);
	void InitPathFinder();

	virtual void FireProjectile(int32 InCount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform);

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
		

protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	virtual void OnPaperBurnEffect(float InDissolve);
	UFUNCTION()
	virtual void OnPaperBurnEffectEnd();

protected:
	UFUNCTION()
	virtual void OnDie();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual float GetMeleeDamage();

public:
	TArray<AActor*> GetNearbyEnemies() { return NearbyEnemies; }

	bool IsKnifeEnemy() { return EnemyData->WeaponType == EWeaponType::WT_Knife; }

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<APathFinder> PathFinderRef;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> HPWidgetComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWeaponChildActorComponent> Weapon;

protected:
	UPROPERTY(VisibleAnywhere)
	UStatusComponent* StatusComponent;

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	USphereComponent* ProximitySphere;

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* PaperBurnEffectTimelineComponent;
	TArray<UMaterialInstanceDynamic*> MaterialInstanceDynamics;

protected:
	// 현재 장착된 무기
	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	EWeaponType CurrentWeaponType;

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/ProjectDD.PawnTableRow"))
	FDataTableRowHandle DataTableRowHandle;

	FPawnTableRow* EnemyData;

	UAnimMontage* CurrentDieMontage;

protected:
	UPROPERTY()
	TArray<AActor*> NearbyEnemies;
};
