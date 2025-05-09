// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/UI_PlayerStatus.h"
#include "SubSystem/ItemInventorySubsystem.h"

void UUI_PlayerStatus::SetDrawUI(FPawnStatusTableRow Status)
{
	if (HPTextBlock == nullptr)
		return;

	HPTextBlock->SetText(FText::Format(NSLOCTEXT("UI", "HP", "HP : {0}/{1}"), 
		FText::AsNumber(Status.HP), FText::AsNumber(Status.MAXHP)));
	ArmorTextBlock->SetText(FText::Format(NSLOCTEXT("UI", "ARMOR", "ARMOR : {0}/{1}"), 
		FText::AsNumber(Status.ARMOR), FText::AsNumber(Status.MAXARMOR)));
	Bullet556mTextBlock->SetText(FText::Format(NSLOCTEXT("UI", "5.56mmCount", "5.56mm : {0}/{1}"), 
		FText::AsNumber(Status.BulletCount556mm), FText::AsNumber(Status.MaxBulletCount556mm)));
	Bullet9mTextBlock->SetText(FText::Format(NSLOCTEXT("UI", "9mmCount", "9mm : {0}/{1}"), 
		FText::AsNumber(Status.BulletCount9mm), FText::AsNumber(Status.MaxBulletCount9mm)));
	GrenadeTextBlock->SetText(FText::Format(NSLOCTEXT("UI", "Grenade", "Grenade : {0}/{1}"), 
		FText::AsNumber(Status.GrenadeCount), FText::AsNumber(Status.MaxGrenadeCount)));

	{
		UItemInventorySubsystem* InvenSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UItemInventorySubsystem>();
		if (!InvenSubsystem)
		{
			return;
		}

		int8 YellowKey = InvenSubsystem->GetKeyByType(EKeyItemType::Key_Yellow) ? 1 : 0;
		int8 BlueKey = InvenSubsystem->GetKeyByType(EKeyItemType::Key_Blue) ? 1 : 0;
		int8 RedKey = InvenSubsystem->GetKeyByType(EKeyItemType::Key_Red) ? 1 : 0;

		YellowKeyTextBlock->SetText(FText::Format(NSLOCTEXT("UI", "YellowKey", "YellowKey : {0}/{1}"),
			FText::AsNumber(YellowKey), FText::AsNumber(1)));
		BlueKeyTextBlock->SetText(FText::Format(NSLOCTEXT("UI", "BlueKey", "BlueKey : {0}/{1}"),
			FText::AsNumber(BlueKey), FText::AsNumber(1)));
		RedKeyTextBlock->SetText(FText::Format(NSLOCTEXT("UI", "RedKey", "RedKey : {0}/{1}"),
			FText::AsNumber(RedKey), FText::AsNumber(1)));
	}


}