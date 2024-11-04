// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "SoftWheelSpringArmComponent.generated.h"

/**
 *
 */
UCLASS()
class PROJECTDD_API USoftWheelSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetDesiredAim(const float InValue);

	UFUNCTION(BlueprintCallable)
	void OnAiming();

	UFUNCTION(BlueprintCallable)
	void OnEndAiming();

	UFUNCTION(BlueprintCallable)
	void SetMinMaxTargetArmLength(const float MinLength, const float MaxLength);

public:
	float GetMinTargetArmLength() const { return MinTargetArmLength; }
	float GetMaxTargetArmLength() const { return MaxTargetArmLength; }

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

protected:
	void UpdateDesiredTargetArmLength(const float DeltaTime);

protected:
	float MinTargetArmLength = 20.f;
	float MaxTargetArmLength = 500.f;

	float DesiredTargetArmLength = TargetArmLength;

	float AimSpeed = 10.f;
};
