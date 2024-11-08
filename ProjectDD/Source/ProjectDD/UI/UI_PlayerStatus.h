// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/PawnStatusData.h"
#include "Components/TextBlock.h"

#include "UI_PlayerStatus.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTDD_API UUI_PlayerStatus : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetDrawUI(FPawnStatusTableRow Status);

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HPTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ArmorTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Bullet556mTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Bullet9mTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GrenadeTextBlock;
};
