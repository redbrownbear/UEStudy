// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Enemy/PathFinder.h"

// Sets default values
APathFinder::APathFinder()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));

	RootComponent = SplineComponent;
}

// Called when the game starts or when spawned
void APathFinder::BeginPlay()
{
	Super::BeginPlay();

	SetFolderPath(FName("FunctionOnly"));
}

// Called every frame
void APathFinder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

