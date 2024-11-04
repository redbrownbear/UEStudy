// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/BaisicCharacterAnimInstance.h"
#include "AIController.h"
#include "PawnData.generated.h"

USTRUCT()
struct PROJECTDD_API FPawnTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Pawn")
	USkeletalMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Pawn")
	FTransform MeshTransform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	TSubclassOf<UBaisicCharacterAnimInstance> AnimClass;

public:
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	TSubclassOf<UShapeComponent> CollisionClass = USphereComponent::StaticClass();
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionSphereRadius = 32.f;
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	FVector CollisionBoxExtent = FVector(32.0, 32.0, 32.0);
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionCapsuleRadius = 22.f;
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionCapsuleHalfHeight = 44.f;

public: // Animation
	UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	TArray<UAnimMontage*> HitReactMontage;
	UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	TArray<UAnimMontage*> DieMontage;

	//Weapon에 따른 Animation변경
	UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	TArray<TSubclassOf<UBaisicCharacterAnimInstance>> WeaponAnimType;

public: // Movement
	UPROPERTY(EditAnywhere, Category = "Pawn|Movement")
	float MovementMaxSpeed = 400.f;

	UPROPERTY(EditAnywhere, Category = "Pawn|Movement")
	float RunMaxSpeed = 650.f;

public: //(Enemy만 적용)
	UPROPERTY(EditAnywhere, Category = "Enemy")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditAnywhere, Category = "Enemy", meta = (RowType = "/Script/ProjectDD.WeaponTableRow"))
	FDataTableRowHandle Weapon;
};