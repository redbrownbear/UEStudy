// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/BaisicCharacterAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Actors/PlayerController/BasicPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

void UBaisicCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* Pawn = TryGetPawnOwner();
	if (GIsEditor && FApp::IsGame() && !Pawn)
	{
		checkf(false, TEXT("UBaisicCharacterAnimInstance를 사용하려면 소유권자가 Pawn이여야 합니다."));
		return;
	}
	else if (!Pawn) { return; }

	MovementComponent = Pawn->GetMovementComponent();
	check(MovementComponent);

	StatusComponent = Pawn->GetComponentByClass<UStatusComponent>();
	check(StatusComponent);
}

void UBaisicCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!MovementComponent) { return; }

	APawn* Pawn = TryGetPawnOwner();
	if (GIsEditor && FApp::IsGame() && !Pawn)
	{
		checkf(false, TEXT("UBaisicCharacterAnimInstance를 사용하려면 소유권자가 Pawn이여야 합니다."));
		return;
	}
	else if (!Pawn) { return; }

	bIsRun = StatusComponent->IsRun();
	
	FVector Velocity = MovementComponent->Velocity;
	Speed = UKismetMathLibrary::VSizeXY(Velocity);

	bShoudMove = !FMath::IsNearlyZero(Speed);

	bIsCrouch = MovementComponent->IsCrouching();
	bIsFalling = MovementComponent->IsFalling();

	if (bShoudMove)
	{
		BackFowardAxis = FVector::DotProduct(Pawn->GetActorForwardVector(), Velocity);//InputActionValue.X;
		LeftRightAxis = FVector::DotProduct(Pawn->GetActorRightVector(), Velocity);//InputActionValue.Y;
	}
}
