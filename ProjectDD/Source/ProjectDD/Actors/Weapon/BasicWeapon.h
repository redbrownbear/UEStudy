// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animation/BaisicCharacterAnimInstance.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StatusComponent.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "Data/WeaponData.h"
#include "Misc/Utils.h"
#include "BasicWeapon.generated.h"


UCLASS()
class PROJECTDD_API ABasicWeapon : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABasicWeapon();

    virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);

    const FWeaponTableRow* GetWeaponTableRow() const { return WeaponTableRow; }

protected: // InputAction callback
    void OnFire(const FInputActionValue& InputActionValue);
    void EndMotion();

    UFUNCTION(BlueprintCallable)
    virtual void Attack();

    UFUNCTION()
    virtual void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted);

    UFUNCTION()
    virtual void OnAim();

    UFUNCTION()
    virtual void EndAim();

protected:
    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* DefaultSceneRoot;

    UPROPERTY(VisibleAnywhere)
    USkeletalMeshComponent* SkeletalMeshComponent;

    UPROPERTY(VisibleAnywhere)
    UParticleSystemComponent* ParticleSystemComponent;

protected: // Owner
    APawn* OwningPawn = nullptr;
    UBaisicCharacterAnimInstance* BasicAnimInstance = nullptr;

    UPROPERTY()
    UStatusComponent* OwnerStatusComponent = nullptr;

protected:
    UPROPERTY(EditAnywhere, meta = (RowType = "/Script/ProjcetDD.WeaponTableRow"))
    FDataTableRowHandle DataTableRowHandle;

    const FWeaponTableRow* WeaponTableRow = nullptr;

protected: // Input
    class USoftWheelSpringArmComponent* SpringArm = nullptr;
    UInputMappingContext* IMC_Weapon = nullptr;
};
