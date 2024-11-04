// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Data/ProjectileData.h"
#include "BasicProjectile.generated.h"

UCLASS()
class PROJECTDD_API ABasicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicProjectile();
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY()
	UProjectileMovementComponent* ProjectileMovementComponent;

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/ProjectDD.ProjectileTableRow"))
	FDataTableRowHandle DataTableRowHandle;

	FProjectileTableRow* ProjectileData;
};
