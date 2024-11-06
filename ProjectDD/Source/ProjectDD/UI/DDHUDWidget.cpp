// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DDHUDWidget.h"
#include "Components/TextBlock.h"

void UDDHUDWidget::NativeConstruct()
{
	AUsableActorDescVerticalBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("AUsableActorDescVerticalBox")));
	if (!AUsableActorDescVerticalBox)
	{
		check(false);
		return;
	}
}

void UDDHUDWidget::AddAUsableActor(AUsableActor* NewActor)
{
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

void UDDHUDWidget::RemoveAUsableActor()
{
	if (AUsableActorDescVerticalBox->GetChildAt(0) != nullptr)
	{
		AUsableActorDescVerticalBox->RemoveChildAt(0);
	}
}