// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"

#include "Handler/ItemEquipHandler.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "Components/StatusComponent.h"

#include "Actors/Player/BasicPlayer.h"
#include "UI/HUD/DDHUD.h"

ABasicPlayerController::ABasicPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
	{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprints/Input/Player/IMC_DD.IMC_DD'") };
	check(Asset.Object);

	IMC_Default = Asset.Object;
}

void ABasicPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetFolderPath(FName("ControllerOnly"));

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->AddMappingContext(IMC_Default, 0);

	// 컨트롤러에 의해 캐릭터가 회전하도록 설정 (Yaw 회전만)a
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		ControlledPawn->bUseControllerRotationYaw = true;  // 캐릭터가 컨트롤러의 회전을 따름
		UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(ControlledPawn->GetMovementComponent());
		if (MovementComponent)
		{
			MovementComponent->bOrientRotationToMovement = false;  // 이동 방향으로 회전하지 않음
		}
	}
}

void ABasicPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Move")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Move is disabled"));
	}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_ChangeRotator")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnChangeRotator);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_ChangeRotator is disabled"));
	}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Crouch")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Ongoing, this, &ThisClass::OnCrouch);
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::OnEndCrouch);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Crouch is disabled"));
	}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Run")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnRun);
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::OnEndRun);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Run is disabled"));
	}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Jump")))
	{
		EnhancedInputComponent->BindAction(InputAction,
			ETriggerEvent::Started, this, &ThisClass::OnJump);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Jump is disabled"));
	}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_InterAct")))
	{
		EnhancedInputComponent->BindAction(InputAction,
			ETriggerEvent::Started, this, &ThisClass::OnInterAct);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_InterAct is disabled"));
	}

	{
		BindingWeapon(EnhancedInputComponent, TEXT("IA_Weapon00"), EWeaponType::WT_None);
		BindingWeapon(EnhancedInputComponent, TEXT("IA_Weapon01"), EWeaponType::WT_Knife);
		BindingWeapon(EnhancedInputComponent, TEXT("IA_Weapon02"), EWeaponType::WT_Pistol);
		BindingWeapon(EnhancedInputComponent, TEXT("IA_Weapon03"), EWeaponType::WT_Rifle);
		BindingWeapon(EnhancedInputComponent, TEXT("IA_Weapon04"), EWeaponType::WT_Grenade);
	}
}

void ABasicPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	StatusComponent = InPawn->GetComponentByClass<UStatusComponent>();
	check(StatusComponent);
}

void ABasicPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABasicPlayerController::OnChangeRotator(const FInputActionValue& InputActionValue)
{
	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();

	AddYawInput(ActionValue.X);
	AddPitchInput(-ActionValue.Y);
}

void ABasicPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	if (StatusComponent && !StatusComponent->CanMove()) { return; }

	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = K2_GetActorRotation();
	const FRotator RotationYaw = FRotator(0.0, Rotation.Yaw, 0.0);
	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(RotationYaw);
	const FVector RightVector = UKismetMathLibrary::GetRightVector(RotationYaw);

	ABasicPlayer* ControlledCharacter = Cast<ABasicPlayer>(GetPawn());
	ControlledCharacter->AddMovementInput(ForwardVector, ActionValue.X);
	ControlledCharacter->AddMovementInput(RightVector, ActionValue.Y);

	InputMoveActionVector = ActionValue;
}

void ABasicPlayerController::OnCrouch(const FInputActionValue& InputActionValue)
{
	if (StatusComponent && !StatusComponent->CanMove()) { return; }
	ABasicPlayer* ControlledCharacter = Cast<ABasicPlayer>(GetPawn());

	ControlledCharacter->Crouch();
}

void ABasicPlayerController::OnEndCrouch(const FInputActionValue& InputActionValue)
{
	CrouchOver();
}

void ABasicPlayerController::OnRun(const FInputActionValue& InputActionValue)
{
	if (StatusComponent && (!StatusComponent->CanMove() || StatusComponent->IsAim())) { return; }

	if (ABasicPlayer* ChildCharacter = Cast<ABasicPlayer>(GetPawn()))
	{
		bool IsForward = InputMoveActionVector.X < 0 ? false : true;
		
		ChildCharacter->SetMoveSpeed(IsForward);
		StatusComponent->SetRun(IsForward);
	}	
}

void ABasicPlayerController::OnEndRun(const FInputActionValue& InputActionValue)
{
	RunOver();	
}

void ABasicPlayerController::OnJump(const FInputActionValue& InputActionValue)
{
	if (StatusComponent && !StatusComponent->CanMove()) { return; }
	ABasicPlayer* ControlledCharacter = Cast<ABasicPlayer>(GetPawn());
	ControlledCharacter->Jump();
}

void ABasicPlayerController::OnInterAct(const FInputActionValue& InputActionValue)
{
	//HUD에 바로 연결하는 식이 아닌 추가 매니저를 만들자...
	ADDHUD* HUD = Cast<ADDHUD>(GetHUD());
	if (HUD == nullptr)
		return;

	if (HUD->GetOverlappedUsableActors().IsEmpty())
		return;

	AUsableActor* UsableActor = static_cast<AUsableActor*>(HUD->GetOverlappedUsableActors()[0]);

	bool isUsable = UsableActor->IsActorUsable();

	UsableActor->OnItemUse(isUsable);
}

void ABasicPlayerController::OnChangeWeapon(const FInputActionValue& InputActionValue, EWeaponType InWeaponType)
{
	if (InputActionValue.Get<bool>())
	{	
		ABasicPlayer* ControlledCharacter = Cast<ABasicPlayer>(GetPawn());
		if (ControlledCharacter)
		{
			ControlledCharacter->SwitchWeaponAnim(InWeaponType);
		}		

		//여기에서 처리
		{
			UItemEquipHandler* ItemHandler = NewObject<UItemEquipHandler>();
			if (!ItemHandler)
			{
				ensureMsgf(false, TEXT("ItemHandler is nullptr"));
				return;
			}

			TUniquePtr<UItemEquipHandler::FContext> Context = MakeUnique<UItemEquipHandler::FContext>();
			Context->User = this;
			Context->ItemType = InWeaponType;
			ItemHandler->SetContext(MoveTemp(Context));
			ItemHandler->Equip();
		}
	}
}

void ABasicPlayerController::CrouchOver()
{
	if (StatusComponent && !StatusComponent->CanMove()) { return; }
	ABasicPlayer* ControlledCharacter = Cast<ABasicPlayer>(GetPawn());
	ControlledCharacter->UnCrouch();
}

void ABasicPlayerController::RunOver()
{
	if (StatusComponent && !StatusComponent->CanMove()) { return; }
	ABasicPlayer* ControlledCharacter = Cast<ABasicPlayer>(GetPawn());
	ControlledCharacter->SetMoveSpeed(false);
	StatusComponent->SetRun(false);
}

void ABasicPlayerController::GetUsableActorFocus()
{
}

void ABasicPlayerController::BindingWeapon(UEnhancedInputComponent* InEnhancedInputComponent, const FName& InName, const EWeaponType& InWeaponType)
{
	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, InName))
	{
		InEnhancedInputComponent->BindActionValueLambda(
			InputAction, ETriggerEvent::Triggered,
			[this, InWeaponType](const FInputActionValue& InputActionValue)
			{
				OnChangeWeapon(InputActionValue, InWeaponType);
			});
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is disabled"), *InName.ToString());
	}
}
