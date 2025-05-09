// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"

#include "UI/InGame/UI_PlayerStatus.h"

#include "Actors/Items/Environment/UsableActor.h"
#include "Data/PawnStatusData.h"

#include "UI_InGameWidget.generated.h"

/**
 * 
 */

UCLASS()
class PROJECTDD_API UUI_InGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void AddUsableActor(AUsableActor* NewActor);
	void RemoveUseActor();
	void RemoveUsableActorsAll();

	UFUNCTION(BlueprintCallable)
	void ShowEmergencyMessage(const FString& Message, float Duration);
	void RemoveEmergencyMessage();

public:
	void UpdateStatus(FPawnStatusTableRow Status);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> ActorDescWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> StatusDescWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UVerticalBox* AUsableActorDescVerticalBox = nullptr;	

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UVerticalBox* AStatusDescVerticalBox = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UUI_PlayerStatus* UIPlayerStatClass = nullptr;

protected:
	FTimerHandle MessageTimerHandle;
};
