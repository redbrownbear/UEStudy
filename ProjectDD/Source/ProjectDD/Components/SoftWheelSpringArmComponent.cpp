// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SoftWheelSpringArmComponent.h"

void USoftWheelSpringArmComponent::SetDesiredAim(const float InValue)
{
	DesiredTargetArmLength = FMath::Clamp(InValue, MinTargetArmLength, MaxTargetArmLength);
}

void USoftWheelSpringArmComponent::OnAiming()
{
	DesiredTargetArmLength = FMath::Clamp(DesiredTargetArmLength - MinTargetArmLength, MinTargetArmLength, MaxTargetArmLength);
}

void USoftWheelSpringArmComponent::OnEndAiming()
{
	DesiredTargetArmLength = FMath::Clamp(DesiredTargetArmLength + MaxTargetArmLength, MinTargetArmLength, MaxTargetArmLength);
}

void USoftWheelSpringArmComponent::SetMinMaxTargetArmLength(const float MinLength, const float MaxLength)
{
	if (MaxLength < MinLength)
	{
		checkf(false, TEXT("MaxTargetArmLength(%f) < MinTargetArmLength(%f)"), MaxTargetArmLength, MinTargetArmLength);
		return;
	}

	MinTargetArmLength = MinLength;
	MaxTargetArmLength = MaxLength;

	/*TargetArmLength = FMath::Max(TargetArmLength, MinTargetArmLength);
	TargetArmLength = FMath::Min(TargetArmLength, MaxTargetArmLength);*/
	TargetArmLength = FMath::Clamp(TargetArmLength, MinTargetArmLength, MaxTargetArmLength);
	DesiredTargetArmLength = TargetArmLength;
}

void USoftWheelSpringArmComponent::UpdateDesiredTargetArmLength(const float DeltaTime)
{
	// Desired에 Target이 도달하면 return
	if (FMath::IsNearlyEqual(TargetArmLength, DesiredTargetArmLength))
	{
		return;
	}

	const float DeltaSpeed = FMath::Clamp(DeltaTime * AimSpeed, 0.f, 1.f);
	TargetArmLength = FMath::Lerp(TargetArmLength, DesiredTargetArmLength, DeltaSpeed);
	TargetArmLength = FMath::Clamp(TargetArmLength, MinTargetArmLength, MaxTargetArmLength);
}

void USoftWheelSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateDesiredTargetArmLength(DeltaTime);
}
