// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Projectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UAnimNotify_Projectile : public UAnimNotify
{
	GENERATED_BODY()

public:
	FRotator GetPlayerProjectileRotation(const FVector& InProjectSpawnLocation, const FVector& InEndLocation);

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	
};
