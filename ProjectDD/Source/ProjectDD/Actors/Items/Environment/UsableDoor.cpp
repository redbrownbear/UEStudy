// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/Environment/UsableDoor.h"
#include "SubSystem/ItemInventorySubsystem.h"
#include "SubSystem/HUDManagerSubsystem.h"


void AUsableDoor::OnItemUse(bool isUsable)
{
	//열쇠 타입과 문타입이 맞아야 열린다.

	UHUDManagerSubsystem* HUDManager = GetWorld()->GetGameInstance()->GetSubsystem<UHUDManagerSubsystem>();
	if (!HUDManager)
	{
		check(false);
		return;
	}

	UItemInventorySubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UItemInventorySubsystem>();
	if (Subsystem)
	{
		if (!Subsystem->GetKeyByType(ActorData.KeyItemType))
		{

			FText FormattedText = FText::Format(
				FText::FromString(TEXT("{name}를 찾으세요")),
				FText::FromName(ActorData.KeyItemName));

			HUDManager->ShowEmergencyMessage(FormattedText.ToString());
			return;
		}
	}


	//문의 회전을 동일하게 하기 위해
	//사실 리소스가 여러개면 하지 않아도 되는 일
	FVector ActorScale = GetActorScale();
	
	float offset = ActorScale.X / FMath::Abs(ActorScale.X);
	if (bIsClose)
	{
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		LocalRotation = -90.0f * offset;
	}
	else
	{
		LocalRotation = 90.0f * offset;
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	}

	FRotator Rotator = MeshComponent->GetComponentRotation();
	FRotator NewRotator = FRotator(Rotator.Pitch, Rotator.Yaw + LocalRotation, Rotator.Roll);
	MeshComponent->SetWorldRotation(NewRotator);

	bIsClose = !bIsClose;
	Super::OnItemUse(isUsable);
}

bool AUsableDoor::IsTrapDoor()
{
	if (!ActorData.bTrap)
		return false;

	// 조건 추가
	
	// 트리거를 활성화 했는가?
	 
	// 트랩방의 적군 혹은 기믹을 완료 했는가?

	return true;
}
