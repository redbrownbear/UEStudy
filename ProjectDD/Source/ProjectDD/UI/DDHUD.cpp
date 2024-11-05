// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DDHUD.h"
#include "Kismet/GameplayStatics.h"

#include "Actors/PlayerController/BasicPlayerController.h"
#include "Actors/Items/Environment/UsableActor.h"

void ADDHUD::AddUsableActor(AUsableActor* NewActor)
{
	Widget->AddAUsableActor(NewActor);
}

void ADDHUD::RemoveUsableActor(AUsableActor* NewActor)
{
	Widget->RemoveAUsableActor(NewActor);
}

void ADDHUD::BeginPlay()
{
	Super::BeginPlay();

	UClass* WidgetClass = LoadClass<UDDHUDWidget>(nullptr,

		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/UI_DDHUD.UI_DDHUD_C'"));
	check(WidgetClass);
	Widget = CreateWidget<UDDHUDWidget>(GetWorld(), WidgetClass);
	Widget->AddToViewport();
}
