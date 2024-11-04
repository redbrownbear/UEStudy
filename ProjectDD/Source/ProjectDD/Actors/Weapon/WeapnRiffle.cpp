// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/WeapnRiffle.h"
#include "Kismet/KismetMathLibrary.h"

void AWeapnRiffle::SetData(const FDataTableRowHandle& InDataTableRowHandle)
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

void AWeapnRiffle::OnAim()
{
	if (!OwnerStatusComponent->CanAttack())
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

	ParticleSystemComponent->SetBeamSourcePoint(0, StartLocation, 0);
	ParticleSystemComponent->SetBeamTargetPoint(0, EndLocation, 0);
}

void AWeapnRiffle::EndAim()
{
	SpringArm->OnEndAiming();
	OwnerStatusComponent->SetAim(false);
	ParticleSystemComponent->DeactivateImmediate();
	EndMotion();
}

void AWeapnRiffle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateDesiredAimRotation(DeltaTime);
}

void AWeapnRiffle::UpdateDesiredAimRotation(const float DeltaTime)
{
	if (!OwnerStatusComponent->CanAttack())
		return;

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
		//NewRotation.Pitch = UKismetMathLibrary::Wrap(NewRotation.Pitch, 0.0, 360.0);
		//NewRotation.Yaw = UKismetMathLibrary::ClampAngle(NewRotation.Yaw, -179.0, 179.0);
		//NewRotation.Roll = UKismetMathLibrary::ClampAngle(NewRotation.Roll, -360.0, 360.0);
		BasicAnimInstance->SetAimRotation(NewRotation);
	}
}
