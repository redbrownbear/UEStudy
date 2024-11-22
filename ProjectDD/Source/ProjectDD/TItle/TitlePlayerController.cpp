// Fill out your copyright notice in the Description page of Project Settings.


#include "TItle/TitlePlayerController.h"

void ATitlePlayerController::BeginPlay()
{
    Super::BeginPlay();

    // 마우스 커서 활성화
    bShowMouseCursor = true;

    // UI 모드 설정
    FInputModeUIOnly InputMode;
    SetInputMode(InputMode);
}
