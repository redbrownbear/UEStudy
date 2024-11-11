// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/Environment/UsableDoor.h"


void AUsableDoor::OnItemUse(bool isUsable)
{
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
