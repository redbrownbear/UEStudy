// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/PawnStatusData.h"

#include "StatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHPChanged, float, CurrentHP, float, MaxHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBulletChanged, int32, CurrentCount, int32, MaxCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTDD_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

	void SetStatus(FDataTableRowHandle InDataTableRowHandle);
	void SetUI();

	void SetAim(const bool bFlag) { bAim = bFlag; }
	bool IsAim()const { return bAim; }

	void SetRun(const bool bFlag) { bIsRun = bFlag; }
	bool IsRun()const { return bIsRun; }
	
	void SetDie(const bool bFlag) { bDie = bFlag; }
	bool IsDie() const { return bDie; }

	void SetAttack(const bool bFlag) { bAttack = bFlag; }
	bool CanMove() const { return !bAttack && !bDie; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	void ProjectileFire(AController* EventInstigator, int32 BulletCount, int32 BulletMaxCount);

	const FPawnStatusTableRow& GetCharacterStatus() { return CharacterStatus; }

protected:
	bool IsPlayer();

public:
	AController* GetLastInstigator() const { return LastInstigator; }

	//댈리게이트 통신을 위함
public:
	AController* LastInstigator = nullptr;

	UPROPERTY(BlueprintAssignable)
	FOnHPChanged OnHPChanged;
	FOnBulletChanged OnBulletChanged;
	FOnDie OnDie;

protected:
	bool bAttack = false;
	bool bAim = false;
	bool bIsRun = false;
	bool bDie = false;

	//캐릭터의 스탯
private:
	FPawnStatusTableRow CharacterStatus;
};