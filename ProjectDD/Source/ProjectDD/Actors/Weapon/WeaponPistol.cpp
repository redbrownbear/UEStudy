// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/WeaponPistol.h"
#include "Kismet/KismetMathLibrary.h"

void AWeaponPistol::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	Super::SetData(InDataTableRowHandle);

	if (WeaponTableRow->ParticleSystem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load Particle System"));
		return;
	}

	ParticleSystemComponent->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName::Muzzle);

	ParticleSystemComponent->SetTemplate(WeaponTableRow->ParticleSystem);
	ParticleSystemComponent->DeactivateImmediate();

	EndAim();
}

void AWeaponPistol::Attack()
{
	if (OwnerStatusComponent->Is9BulletEmpty() && OwningPawn->IsA(ABasicPlayer::StaticClass()))
	{
		UHUDManagerSubsystem* HUDManager = GetWorld()->GetGameInstance()->GetSubsystem<UHUDManagerSubsystem>();
		if (!HUDManager)
		{
			check(false);
			return;
		}

		HUDManager->ShowEmergencyMessage(TEXT("권총 총알이 부족합니다."));
		return;
	}

	Super::Attack();
}

void AWeaponPistol::OnAim()
{
	//rifle과 합치는게 좋겠다...
	if (OwnerStatusComponent->IsRun())
		return;

	if (!OwnerStatusComponent->IsAim())
	{
		OwnerStatusComponent->SetAim(true);
		ParticleSystemComponent->Activate(false);
	}

	SpringArm->OnAiming();

	MuzzleTransform = SkeletalMeshComponent->GetSocketTransform(SocketName::Muzzle);

	FVector StartLocation = MuzzleTransform.GetLocation();
	FVector EndLocation = StartLocation + (MuzzleTransform.GetRotation().Vector() * 10000.0f);
	FHitResult HitResult;

	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);

	if (HitResult.bBlockingHit)
	{
		EndLocation = HitResult.ImpactPoint;
	}

	ParticleSystemComponent->SetBeamTargetPoint(0, EndLocation, 0);
}

void AWeaponPistol::EndAim()
{
	if (!SpringArm)
		return;

	SpringArm->OnEndAiming();
	OwnerStatusComponent->SetAim(false);
	ParticleSystemComponent->DeactivateImmediate();
	EndMotion();
}

void AWeaponPistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateDesiredAimRotation(DeltaTime);
}

void AWeaponPistol::UpdateDesiredAimRotation(const float DeltaTime)
{
	{
		const FRotator OwnerRotation = OwningPawn->GetActorRotation();
		FRotator OwnerInvRotation = OwnerRotation.GetInverse();
		OwnerInvRotation.Roll = 0.;
		FRotator ControlRotation = OwningPawn->GetControlRotation();
		ControlRotation.Roll = 0.;
		FRotator NewRotation = UKismetMathLibrary::ComposeRotators(OwnerInvRotation, ControlRotation);

		DesiredAimRotation.Pitch = NewRotation.Pitch;
		DesiredAimRotation.Yaw = UKismetMathLibrary::ClampAngle(NewRotation.Yaw, -100.0, 100.0);
		DesiredAimRotation.Roll = NewRotation.Roll;
	}
	{
		const float NewDeltaTime = FMath::Clamp(DeltaTime, 0.f, 0.03f);
		const FRotator& AimRotation = BasicAnimInstance->GetAimRotation();
		const float Alpha = NewDeltaTime * 10.f;
		const FRotator LerpShortestPathRotation = UKismetMathLibrary::RLerp(AimRotation, DesiredAimRotation, Alpha, true);
		const FRotator LerpRotation = UKismetMathLibrary::RLerp(AimRotation, DesiredAimRotation, Alpha, false);
		FRotator NewRotation = FRotator(LerpShortestPathRotation.Pitch, LerpRotation.Yaw, LerpShortestPathRotation.Roll);
		BasicAnimInstance->SetAimRotation(NewRotation);
	}
}
