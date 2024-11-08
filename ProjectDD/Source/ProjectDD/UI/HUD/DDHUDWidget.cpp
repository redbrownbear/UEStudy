// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/DDHUDWidget.h"
#include "Components/TextBlock.h"

void UDDHUDWidget::NativeConstruct()
{
	AUsableActorDescVerticalBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("AUsableActorDescVerticalBox")));
	if (!AUsableActorDescVerticalBox)
	{
		check(false);
		return;
	}

	UIPlayerStatClass = Cast<UUI_PlayerStatus>(GetWidgetFromName(TEXT("UI_Player_Status")));
	if (!UIPlayerStatClass)
	{
		check(false);
		return;
	}
}

void UDDHUDWidget::AddUsableActor(AUsableActor* NewActor)
{
	//하나만 표기
	if (AUsableActorDescVerticalBox->GetChildAt(0) != nullptr)
		return;

	if (UUserWidget * ActorDescWidget = CreateWidget<UUserWidget>(GetWorld(), ActorDescWidgetClass))
	{	
		UTextBlock* ActorDescriptionText = Cast<UTextBlock>(ActorDescWidget->GetWidgetFromName(TEXT("UI_Usable_Actor_Desc")));
		if (ActorDescriptionText)
		{
			ActorDescriptionText->SetText(FText::FromString(NewActor->GetUseActionText().ToString()));
		}

		AUsableActorDescVerticalBox->AddChild(ActorDescWidget);
	}
}

void UDDHUDWidget::RemoveUseActor(AUsableActor* NewActor)
{

}

void UDDHUDWidget::RemoveUsableActorsAll()
{
	if (AUsableActorDescVerticalBox->GetChildAt(0) != nullptr)
	{
		AUsableActorDescVerticalBox->ClearChildren();
	}
}

void UDDHUDWidget::UpdateStatus(FPawnStatusTableRow Status)
{
	UIPlayerStatClass->SetDrawUI(Status);
}