// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WeaponChildActorComponent.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "Components/StatusComponent.h"
#include "Data/PawnData.h"
#include "Enum/WeaponType.h"
#include "Misc/Utils.h"

#include "BasicPlayer.generated.h"

UCLASS()
class PROJECTDD_API ABasicPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);

protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust);
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust);
	
public:	
	virtual void SwitchWeaponAnim(EWeaponType NewWeapon);	//컨트롤러에서 무기를 바꿔주기 위함	
	virtual void SetMoveSpeed(const bool IsRun);			//Shift키로 moveSpeed 변경

	virtual void FireProjectile(int32 InCount);

private:
	int32 GetWeaponAnimIdx(EWeaponType InWeapon);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<USoftWheelSpringArmComponent> SpringArm;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWeaponChildActorComponent> Weapon;

	UPROPERTY(VisibleAnywhere)
	UStatusComponent* StatusComponent;

protected:
	// 현재 장착된 무기
	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	EWeaponType CurrentWeaponType;

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/ProjectDD.PawnTableRow"))
	FDataTableRowHandle DataTableRowHandle;
	FPawnTableRow* CharacterData;

protected:
	APlayerController* PlayerController = nullptr;
};
