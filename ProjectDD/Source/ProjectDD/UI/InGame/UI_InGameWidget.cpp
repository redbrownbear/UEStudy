// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_InGameWidget.h"
#include "Components/TextBlock.h"

void UUI_InGameWidget::NativeConstruct()
{
	AUsableActorDescVerticalBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("AUsableActorDescVerticalBox")));
	if (!AUsableActorDescVerticalBox)
	{
		check(false);
		return;
	}
	AStatusDescVerticalBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("AStatusDescVerticalBox")));
	if (!AStatusDescVerticalBox)
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

void UUI_InGameWidget::AddUsableActor(AUsableActor* NewActor)
{
	//하나만 표기
	if (AUsableActorDescVerticalBox->GetChildAt(0) != nullptr)
		return;

	if (UUserWidget * ActorDescWidget = CreateWidget<UUserWidget>(GetWorld(), ActorDescWidgetClass))
	{	
		UTextBlock* ActorDescriptionText = Cast<UTextBlock>(ActorDescWidget->GetWidgetFromName(TEXT("UsableActorDesc")));
		if (ActorDescriptionText)
		{
			ActorDescriptionText->SetText(FText::FromString(NewActor->GetUseActionText().ToString()));
		}

		AUsableActorDescVerticalBox->AddChild(ActorDescWidget);
	}
}

void UUI_InGameWidget::RemoveUseActor()
{
	if (AUsableActorDescVerticalBox->GetChildAt(0) == nullptr)
		return;

	if (UUserWidget* ActorDescWidget = CreateWidget<UUserWidget>(GetWorld(), ActorDescWidgetClass))
	{
		AUsableActorDescVerticalBox->RemoveChildAt(0);
	}
}

void UUI_InGameWidget::RemoveUsableActorsAll()
{
	if (AUsableActorDescVerticalBox->GetChildAt(0) != nullptr)
	{
		AUsableActorDescVerticalBox->ClearChildren();
	}
}

void UUI_InGameWidget::ShowEmergencyMessage(const FString& Message, float Duration)
{
	//하나만 표기
	if (AStatusDescVerticalBox->GetChildAt(0) != nullptr)
		return;

	if (UUserWidget* ActorDescWidget = CreateWidget<UUserWidget>(GetWorld(), StatusDescWidgetClass))
	{
		UTextBlock* ActorDescriptionText = Cast<UTextBlock>(ActorDescWidget->GetWidgetFromName(TEXT("StatusDesc")));
		if (ActorDescriptionText)
		{
			ActorDescriptionText->SetText(FText::FromString(Message));
		}

		AStatusDescVerticalBox->AddChild(ActorDescWidget);
		GetWorld()->GetTimerManager().SetTimer(MessageTimerHandle, this, &UUI_InGameWidget::RemoveEmergencyMessage, Duration, false);
	}
}

void UUI_InGameWidget::RemoveEmergencyMessage()
{
	if (AStatusDescVerticalBox->GetChildAt(0) != nullptr)
	{
		AStatusDescVerticalBox->ClearChildren();
	}

	GetWorld()->GetTimerManager().ClearTimer(MessageTimerHandle);
}

void UUI_InGameWidget::UpdateStatus(FPawnStatusTableRow Status)
{
	UIPlayerStatClass->SetDrawUI(Status);
}