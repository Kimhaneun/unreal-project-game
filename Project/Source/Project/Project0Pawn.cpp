// Fill out your copyright notice in the Description page of Project Settings.


#include "Project0Pawn.h"

// Sets default values
AProject0Pawn::AProject0Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProject0Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProject0Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AProject0Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

