// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/HUDManagerSubsystem.h"
#include "Data/PawnStatusData.h"

void UHUDManagerSubsystem::SetHUD()
{
    if (UWorld* World = GetWorld())
    {
        // 플레이어 컨트롤러를 가져와 HUD를 찾기
        if (APlayerController* PlayerController = World->GetFirstPlayerController())
        {
            HUD = Cast<ADDHUD>(PlayerController->GetHUD());
        }
    }
}

void UHUDManagerSubsystem::AddOverlappedUsableActor(AUsableActor* InOverlappedUsableActor)
{
    if (OverlappedUsableActor.Contains(InOverlappedUsableActor))
        return;

	OverlappedUsableActor.Add(InOverlappedUsableActor);
    HUD->AddUsableActor(InOverlappedUsableActor);
}

void UHUDManagerSubsystem::RemoveUnUsebleActor(AUsableActor* InUnUsableActors)
{
    if (!OverlappedUsableActor.Contains(InUnUsableActors))
        return;

    OverlappedUsableActor.Remove(InUnUsableActors);
    HUD->RemoveUseActor(InUnUsableActors);
}

void UHUDManagerSubsystem::RemoveAllUsableActor()
{
    OverlappedUsableActor.Empty();
    HUD->RemoveUsableActorsAll();
}

void UHUDManagerSubsystem::SetStatus(FPawnStatusTableRow Status)
{
    PlayerStatusData = Status; 
}

void UHUDManagerSubsystem::DrawStatusUI()
{
    HUD->SetStatus(PlayerStatusData);
}
