// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DDHUD.h"

void ADDHUD::BeginPlay()
{
	Super::BeginPlay();

	UClass* WidgetClass = LoadClass<UDDHUDWidget>(nullptr,

		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/UI_DDHUD.UI_DDHUD_C'"));
	check(WidgetClass);
	Widget = CreateWidget<UDDHUDWidget>(GetWorld(), WidgetClass);
	Widget->AddToViewport();
}

void ADDHUD::Tick(float DeltaSeconds)
{

}
