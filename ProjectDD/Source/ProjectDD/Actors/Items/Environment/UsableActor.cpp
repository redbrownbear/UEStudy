// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/Environment/UsableActor.h"

// Sets default values
AUsableActor::AUsableActor()
	: ItemName("")
	, ItemAction("")
	, IsUsable(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//맵자체가 데이터화 된다면 
	//OnConstruction을 추가해서 넣을것
	SetData();
}

void AUsableActor::OnItemUse(bool isUse)
{
	//기능구현
}

FText AUsableActor::GetUseActionText()
{
	FText FormattedText = FText::Format(
		FText::FromString(TEXT("{name} {action}키를 누르세요.")),
		FText::FromName(ItemName),
		FText::FromName(ItemAction)
	);

	return FormattedText;
}

void AUsableActor::SetData()
{
	//여기에 테이블 추가

	ItemAction = TEXT("E");
	ItemName = TEXT("문");
}

void AUsableActor::EndOutlineFocus()
{
}

void AUsableActor::BeginOutlineFocus()
{
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

