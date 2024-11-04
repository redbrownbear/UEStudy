// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Player/MainPlayer.h"

AMainPlayer::AMainPlayer()
{
	//데이터화 가능
	//캐릭터의 시점 변경
	//추후 함수를 추가해 FPS형식으로도 바꾸기
	SpringArm->SetRelativeLocation(FVector(0., 0., 160.));
	Camera->SetRelativeLocation(FVector(120.0, 55.0, 0.0));
	Camera->SetRelativeRotation(FRotator(-5., 0., 0.));
}
