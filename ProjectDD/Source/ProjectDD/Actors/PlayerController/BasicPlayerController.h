// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/DataAsset.h"
#include "Enum/WeaponType.h"
#include "Misc/Utils.h"

#include "Actors/Items/Environment/UsableActor.h"

#include "BasicPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasicPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	/**
	 * Overridable native function for when this controller is asked to possess a pawn.
	 * @param InPawn The Pawn to be possessed
	 */
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	void OnChangeRotator(const FInputActionValue& InputActionValue);
	void OnMove(const FInputActionValue& InputActionValue);
	void OnCrouch(const FInputActionValue& InputActionValue);
	void OnEndCrouch(const FInputActionValue& InputActionValue);
	void OnRun(const FInputActionValue& InputActionValue);
	void OnEndRun(const FInputActionValue& InputActionValue);
	void OnJump(const FInputActionValue& InputActionValue);
	void OnInterAct(const FInputActionValue& InputActionValue);

	void OnChangeWeapon(const FInputActionValue& InputActionValue, EWeaponType InWeaponType);

public:
	void CrouchOver();
	void RunOver();
	void GetUsableActorFocus();

	const FVector2D& GetMoveInputActionVector() { return InputMoveActionVector; }
	const bool IsRunState() { return bIsRun; }

private:
	void BindingWeapon(UEnhancedInputComponent* InEnhancedInputComponent, const FName& InName, const EWeaponType& InWeaponType);
	void CheckForInteractableActor();

protected:
	UInputMappingContext* IMC_Default = nullptr;

	UPROPERTY()
	TArray<AUsableActor*> OverlappedUsableActors;

	UPROPERTY(BlueprintReadWrite)
	bool bIsAiming = false;

	UPROPERTY()
	class UStatusComponent* StatusComponent;

	UPROPERTY()
	FVector2D InputMoveActionVector;

	bool bIsRun;
};
