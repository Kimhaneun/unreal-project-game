// Fill out your copyright notice in the Description page of Project Settings.


#include "MainActor.h"
#include "Project0Actor.h"

// Sets default values
AMainActor::AMainActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AProject0Actor> FindMeshReference(TEXT("/Script/Engine.Blueprint'/Game/01BluePrints/BP_Project0Actor.BP_Project0Actor'_C"));

	if (FindMeshReference.Succeeded())
		BPProject0ActorClass = FindMeshReference.Class;
}

// Called when the game starts or when spawned
void AMainActor::BeginPlay()
{
	Super::BeginPlay();

#pragma region CREATE PROJECT0ACTOR
	FVector Location(0.0f, 0.0f, 0.0f);
	// (x, z, y)
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	// AProject0Actor = GetWorld()->SpawnActor<AProject0Actor>(Location, Rotation);
#pragma endregion

#pragma region DELETE PROJECT0ACTOR
	// Delete after 5 seconds.
	// Project0Actor->SetLifeSpan(5.0f);	

	// Destroy the actor.
	// GetWorld()->DestroyActor(AProject0Actor);
#pragma endregion

	Project0Actor = Cast<AProject0Actor>(GetWorld()->SpawnActor(BPProject0ActorClass));
}

// Called every frame
void AMainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

