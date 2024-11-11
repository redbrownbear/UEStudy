// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/Environment/UsableActor.h"

// Sets default values
AUsableActor::AUsableActor()
	: IsUsable(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetFolderPath(FName("ActorOnly"));
}

void AUsableActor::OnItemUse(bool isUse)
{
	//기능구현
}

FText AUsableActor::GetUseActionText()
{
	FText FormattedText = FText::Format(
		FText::FromString(TEXT("{name} {action}")),
		FText::FromName(ActorData.ItemName),
		FText::FromName(ActorData.ItemAction)
	);

	return FormattedText;
}

void AUsableActor::SetData(const FUsableActorTableRow& InActorData)
{
	ActorData = InActorData;
}

// Called when the game starts or when spawned
void AUsableActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AUsableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

