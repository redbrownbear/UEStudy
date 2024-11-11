// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Enum/KeyItemType.h"
#include "UsableActorData.generated.h"

/**
 * 
 */
class AUsableActor;

USTRUCT()
struct PROJECTDD_API FUsableActorTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Actor")
	TSubclassOf<AUsableActor> UsableActor;
	
	UPROPERTY(EditAnywhere, Category = "Actor")
	FTransform MeshTransform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "Actor")
	bool bCanPickUp = false;

	UPROPERTY(EditAnywhere, Category = "Key")
	EKeyItemType KeyItemType;

	UPROPERTY(EditAnywhere, Category = "TEXT")
	FName ItemAction;

	UPROPERTY(EditAnywhere, Category = "TEXT")
	FName ItemName;
};
