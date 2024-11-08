// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Player/MainPlayer.h"
#include "SubSystem//HUDManagerSubsystem.h"
#include "Engine/OverlapResult.h"

AMainPlayer::AMainPlayer()
{

}

void AMainPlayer::Tick(float DeltaTime)
{
	CheckForInteractableActor();

	Super::Tick(DeltaTime);
}


void AMainPlayer::CheckForInteractableActor()
{
	PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController == nullptr)
		return;

	HUD = Cast<ADDHUD>(PlayerController->GetHUD());
	if (HUD == nullptr)
		return;

	UHUDManagerSubsystem* HUDManager = GetWorld()->GetGameInstance()->GetSubsystem<UHUDManagerSubsystem>();
	if (!HUDManager)
	{
		check(false);
		return;
	}

	Params.AddIgnoredActor(this);

	FVector ForwardVector = GetActorRotation().Vector();
	FVector BoxCenter = GetActorLocation() + (ForwardVector * 70.0f) + FVector(0.0f, 0.0f, 0.0f);
	FVector BoxExtent = FVector(90.0f, 70.0f, 70.0f);

	FVector3f BoxExtent3F = FVector3f(BoxExtent);
	BoxShape.SetBox(BoxExtent3F);

	TArray<FOverlapResult> OverlapResults;
	bool bOverlapping = GetWorld()->OverlapMultiByChannel(OverlapResults, BoxCenter, GetActorRotation().Quaternion(), ECC_Visibility, BoxShape, Params);

	if (!HUDManager->GetOverlappedUsableActors().IsEmpty())
	{
		HUDManager->RemoveAllUsableActor();
	}

	if (bOverlapping)
	{
		// 새롭게 감지된 액터 처리
		for (const FOverlapResult& NewResult : OverlapResults)
		{
			AUsableActor* OverlappingActor = Cast<AUsableActor>(NewResult.GetActor());
			if (OverlappingActor)
			{						
				if(!HUDManager->GetOverlappedUsableActors().Contains(OverlappingActor))
				{
					HUDManager->AddOverlappedUsableActor(static_cast<AUsableActor*>(OverlappingActor));
				}
			}
		}
	}
}
