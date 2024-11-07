// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"

#include "Actors/Items/Environment/UsableActor.h"

#include "DDHUDWidget.generated.h"

/**
 * 
 */

UCLASS()
class PROJECTDD_API UDDHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void AddAUsableActor(AUsableActor* NewActor);
	void RemoveAUsableActor();

protected:
	UVerticalBox* AUsableActorDescVerticalBox = nullptr;	

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> ActorDescWidgetClass = nullptr;
};
