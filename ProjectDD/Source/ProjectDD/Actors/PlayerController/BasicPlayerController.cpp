// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"

#include "Components/SoftWheelSpringArmComponent.h"
#include "Components/StatusComponent.h"

#include "Actors/Player/BasicPlayer.h"
#include "UI/DDHUD.h"

#include "Handler/ItemEquipHandler.h"


ABasicPlayerController::ABasicPlayerController()
{
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

	// 컨트롤러에 의해 캐릭터가 회전하도록 설정 (Yaw 회전만)
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
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnCrouch);
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
			ETriggerEvent::Started, this, &ThisClass::OnJump);
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

	CheckForInteractableActor();
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

	APawn* ControlledPawn = GetPawn();
	ControlledPawn->AddMovementInput(ForwardVector, ActionValue.X);
	ControlledPawn->AddMovementInput(RightVector, ActionValue.Y);

	InputMoveActionVector = ActionValue;
}

void ABasicPlayerController::OnCrouch(const FInputActionValue& InputActionValue)
{
	if (StatusComponent && !StatusComponent->CanMove()) { return; }
	ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn());

	ControlledCharacter->Crouch();
}

void ABasicPlayerController::OnEndCrouch(const FInputActionValue& InputActionValue)
{
	CrouchOver();
}

void ABasicPlayerController::OnRun(const FInputActionValue& InputActionValue)
{
	//플레이어 전용
	if (StatusComponent && (!StatusComponent->CanMove() || StatusComponent->CanAttack())) { return; }

	ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn());
	FVector Direction = ControlledCharacter->GetMovementComponent()->Velocity;
	if (Direction.X <= 0) { return; }
	
	if (ABasicPlayer* ChildCharacter = Cast<ABasicPlayer>(ControlledCharacter))
	{
		ChildCharacter->SetMoveSpeed(true);
		bIsRun = true;
	}	
}

void ABasicPlayerController::OnEndRun(const FInputActionValue& InputActionValue)
{
	//플레이어 전용
	//시간 나면 클래스하나 더 만들어서 상속받아쓰기

	RunOver();
	bIsRun = false;
}

void ABasicPlayerController::OnJump(const FInputActionValue& InputActionValue)
{
	if (StatusComponent && !StatusComponent->CanMove()) { return; }
	ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn());
	ControlledCharacter->Jump();
}

void ABasicPlayerController::OnInterAct(const FInputActionValue& InputActionValue)
{
	if (OverlappedUsableActors.IsEmpty()) { return; }

	AUsableActor* UsableActor = static_cast<AUsableActor*>(*OverlappedUsableActors.begin());

	bool isUsable = UsableActor->IsActorUsable();

	UsableActor->OnItemUse(isUsable);
	UsableActor->SetActorUsable(!isUsable);
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
	ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn());
	ControlledCharacter->UnCrouch();
}

void ABasicPlayerController::RunOver()
{
	if (StatusComponent && !StatusComponent->CanMove()) { return; }
	ABasicPlayer* ControlledCharacter = Cast<ABasicPlayer>(GetPawn());
	ControlledCharacter->SetMoveSpeed(false);
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

void ABasicPlayerController::CheckForInteractableActor()
{
	ADDHUD* HUD = Cast<ADDHUD>(GetHUD());
	if (HUD == nullptr)
		return;

	float CenterZoneRadius = 100.0f; // 중심 부분 영역 크기
	float InteractionDistance = 200.0f; // 상호작용 최대 거리

	int32 ScreenSizeX, ScreenSizeY;
	GetViewportSize(ScreenSizeX, ScreenSizeY);
	FVector2D ScreenCenter = FVector2D(ScreenSizeX / 2.0f, ScreenSizeY / 2.0f);

	FVector WorldLocation, WorldDirection;
	DeprojectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, WorldLocation, WorldDirection);

	FVector End = WorldLocation + (WorldDirection * InteractionDistance);

	// 라인 트레이스 구성
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetPawn());

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, End, ECC_Visibility, Params);
	if (HUD)
	{	
		if (bHit)
		{
			AActor* HitActor = HitResult.GetActor();
			if (HitActor /*&& HitActor->IsA<AUsableActor>()*/)
			{
				if (HitActor != HUD->GetOverlappedUsableActor())
				{
					HUD->AddUsableActor(static_cast<AUsableActor*>(HitActor));
				}
			}
		}		
		else
		{
			HUD->RemoveUsableActor(static_cast<AUsableActor*>(HUD->GetOverlappedUsableActor()));
		}
	}
}
