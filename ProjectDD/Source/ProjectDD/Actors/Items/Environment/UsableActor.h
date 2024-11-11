// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetInteractionComponent.h"
#include "Data/UsableActorData.h"

#include "UsableActor.generated.h"

UCLASS()
class PROJECTDD_API AUsableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUsableActor();

	virtual void OnItemUse(bool isUse);

	virtual void SetActorUsable(bool isUsable) { IsUsable = isUsable; }
	virtual bool IsActorUsable() { return IsUsable; }
	
	virtual FText GetUseActionText();

public:
	virtual void SetData(const FUsableActorTableRow& InActorData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

protected:
	FUsableActorTableRow ActorData;

protected:
	bool IsUsable;
};
