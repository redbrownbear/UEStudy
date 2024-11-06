// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Player/MainPlayer.h"
#include "Engine/OverlapResult.h"

AMainPlayer::AMainPlayer()
{
	//데이터화 가능
	//캐릭터의 시점 변경
	//추후 함수를 추가해 FPS형식으로도 바꾸기
	SpringArm->SetRelativeLocation(FVector(0., 0., 160.));
	Camera->SetRelativeLocation(FVector(120.0, 55.0, 0.0));
	Camera->SetRelativeRotation(FRotator(-5., 0., 0.));
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

	if (HUD)
	{
		TArray<FOverlapResult> OverlapResults;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FVector ForwardVector = GetActorRotation().Vector();
		FVector BoxCenter = GetActorLocation() + (ForwardVector * 70.0f) + FVector(0.0f, 0.0f, 0.0f);
		FVector BoxExtent = FVector(90.0f, 70.0f, 70.0f);

		FCollisionShape BoxShape;
		FVector3f BoxExtent3F = FVector3f(BoxExtent);
		BoxShape.SetBox(BoxExtent3F);

		bool bOverlapping = GetWorld()->OverlapMultiByChannel(OverlapResults, BoxCenter, GetActorRotation().Quaternion(), ECC_Visibility, BoxShape, Params);

		if (bOverlapping)
		{
			// 감지된 액터 처리
			for (const FOverlapResult& Result : OverlapResults)
			{
				AUsableActor* OverlappingActor = Cast<AUsableActor>(Result.GetActor());
				if (OverlappingActor)
				{
					//TArray에서 찾는 로직 추가
					if (!IsActorCorrect(OverlappingActor))
					{
						HUD->AddUsableActor(static_cast<AUsableActor*>(OverlappingActor));
						HUD->SetOverlappedUsableActor(OverlappingActor);
						break;
					}
				}
			}
		}
		else
		{
			if (!HUD->GetOverlappedUsableActors().IsEmpty())
			{
				HUD->RemoveUsableActor(nullptr);
				HUD->SetRemoveAllUsableActor();
			}
		}
	}
}

bool AMainPlayer::IsActorCorrect(AUsableActor* InUsableActor)
{
	if (HUD->GetOverlappedUsableActors().IsEmpty())
		return false;

	for (const AUsableActor* usableActor : HUD->GetOverlappedUsableActors())
	{
		if (usableActor == InUsableActor)
			return true;
	}

	return false;
}
