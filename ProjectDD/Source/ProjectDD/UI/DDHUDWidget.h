// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "DDHUDWidget.generated.h"

/**
 * 
 */

class AUsableActor;

UCLASS()
class PROJECTDD_API UDDHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	friend class DDHUD;

public:
	void AddAUsableActor(AUsableActor* NewItem);
	void RemoveAUsableActor(AUsableActor* NewItem);

protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "AddAUsableActor"))
	void ReceiveAddAUsableActor();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "RemoveAUsableActor"))
	void ReceiveRemoveAUsableActor();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* AUsableActorDescVerticalBox = nullptr;
	
};
