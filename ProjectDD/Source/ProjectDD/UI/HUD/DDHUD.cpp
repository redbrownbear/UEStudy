// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/DDHUD.h"
#include "SubSystem//HUDManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"

void ADDHUD::AddUsableActor(AUsableActor* NewActor)
{
	Widget->AddUsableActor(NewActor);
}

void ADDHUD::RemoveUseActor()
{
	Widget->RemoveUseActor();
}

void ADDHUD::RemoveUsableActorsAll()
{
	Widget->RemoveUsableActorsAll();
}

void ADDHUD::SetStatus(FPawnStatusTableRow Status)
{
	Widget->UpdateStatus(Status);
}

void ADDHUD::BeginPlay()
{
	Super::BeginPlay();
	
	{
		UClass* WidgetClass = LoadClass<UDDHUDWidget>(nullptr,
			TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/UI_DDHUD.UI_DDHUD_C'"));
		check(WidgetClass);
		Widget = CreateWidget<UDDHUDWidget>(GetWorld(), WidgetClass);
		Widget->AddToViewport();
	}

	UHUDManagerSubsystem* HUDManager = GetWorld()->GetGameInstance()->GetSubsystem<UHUDManagerSubsystem>();
	if (HUDManager)
	{
		HUDManager->SetHUD();
		HUDManager->DrawStatusUI();
	}
}
