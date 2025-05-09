// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/DDHUD.h"
#include "SubSystem//HUDManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"

void ADDHUD::BeginPlay()
{
	Super::BeginPlay();

	{
		UClass* WidgetClass = LoadClass<UUI_InGameWidget>(nullptr,
			TEXT("/Game/Blueprints/UI/MAIN/UI_InGameWidget.UI_InGameWidget_C"));
		check(WidgetClass);
		Widget = CreateWidget<UUI_InGameWidget>(GetWorld(), WidgetClass);
		Widget->AddToViewport();
	}

	UHUDManagerSubsystem* HUDManager = GetWorld()->GetGameInstance()->GetSubsystem<UHUDManagerSubsystem>();
	if (HUDManager)
	{
		HUDManager->SetHUD();
		HUDManager->DrawStatusUI();
	}
}



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

void ADDHUD::ShowEmergencyStatus(const FString& Message)
{
	float Duration = 3.0f;
	Widget->ShowEmergencyMessage(Message, Duration);
}

void ADDHUD::ShowDie()
{	
	UClass* WidgetClass = LoadClass<UUserWidget>(nullptr,
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/UI_PlayerDie.UI_PlayerDie_C'"));
	check(WidgetClass);
	UUserWidget* otherWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	otherWidget->AddToViewport();
}
