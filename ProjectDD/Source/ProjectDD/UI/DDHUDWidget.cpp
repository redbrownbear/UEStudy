// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DDHUDWidget.h"

void UDDHUDWidget::AddAUsableActor(AUsableActor* NewItem)
{
	ReceiveAddAUsableActor();
}

void UDDHUDWidget::RemoveAUsableActor(AUsableActor* NewItem)
{
	ReceiveRemoveAUsableActor();
}
