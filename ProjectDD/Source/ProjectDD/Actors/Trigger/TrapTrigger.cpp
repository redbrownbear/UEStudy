// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Trigger/TrapTrigger.h"

// Sets default values
ATrapTrigger::ATrapTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATrapTrigger::TrapActive()
{

}

void ATrapTrigger::TrapEnd()
{
}

// Called when the game starts or when spawned
void ATrapTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

