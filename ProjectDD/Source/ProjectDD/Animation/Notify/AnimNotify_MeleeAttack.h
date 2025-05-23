// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UAnimNotify_MeleeAttack : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_MeleeAttack();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
