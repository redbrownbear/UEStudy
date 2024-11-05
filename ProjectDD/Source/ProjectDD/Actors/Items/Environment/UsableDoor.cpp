// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/Environment/UsableDoor.h"


void AUsableDoor::OnItemUse(bool isUsed)
{
	if (isUsed)
	{
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		LocalRotation = -90.0f;
	}
	else
	{
		LocalRotation = 90.0f;
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	}

	FRotator Rotator = MeshComponent->GetComponentRotation();
	FRotator NewRotator = FRotator(Rotator.Pitch, Rotator.Yaw + LocalRotation, Rotator.Roll);
	MeshComponent->SetWorldRotation(NewRotator);

	Super::OnItemUse(isUsed);
}
