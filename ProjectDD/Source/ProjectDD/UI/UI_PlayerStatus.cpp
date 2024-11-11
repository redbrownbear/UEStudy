// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UI_PlayerStatus.h"

void UUI_PlayerStatus::SetDrawUI(FPawnStatusTableRow Status)
{
	if (HPTextBlock == nullptr)
		return;

	HPTextBlock->SetText(FText::Format(NSLOCTEXT("UI", "HP", "{0}/{1}"), 
		FText::AsNumber(Status.HP), FText::AsNumber(Status.MAXHP)));
	ArmorTextBlock->SetText(FText::Format(NSLOCTEXT("UI", "ARMOR", "{0}/{1}"), 
		FText::AsNumber(Status.ARMOR), FText::AsNumber(Status.MAXARMOR)));
	Bullet556mTextBlock->SetText(FText::Format(NSLOCTEXT("UI", "5.56mmCount", "{0}/{1}"), 
		FText::AsNumber(Status.BulletCount556mm), FText::AsNumber(Status.MaxBulletCount556mm)));
	Bullet9mTextBlock->SetText(FText::Format(NSLOCTEXT("UI", "9mmCount", "{0}/{1}"), 
		FText::AsNumber(Status.BulletCount9mm), FText::AsNumber(Status.MaxBulletCount9mm)));
	GrenadeTextBlock->SetText(FText::Format(NSLOCTEXT("UI", "Grenade", "{0}/{1}"), 
		FText::AsNumber(Status.GrenadeCount), FText::AsNumber(Status.MaxGrenadeCount)));
}