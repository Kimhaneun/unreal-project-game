// Fill out your copyright notice in the Description page of Project Settings.


#include "MainActor.h"
#include "Project0Actor.h"

// Sets default values
AMainActor::AMainActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AProject0Actor> FindMeshReference(TEXT("_C"));

	if (FindMeshReference.Succeeded())
		BPProject0ActorClass = FindMeshReference.Class;
}

// Called when the game starts or when spawned
void AMainActor::BeginPlay()
{
	Super::BeginPlay();

	FVector Location(0.0f, 0.0f, 0.0f);
	// (x, z, y)
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	// AProject0Actor = GetWorld()->SpawnActor<AProject0Actor>(Location, Rotation);

	Project0Actor = Cast<AProject0Actor>(GetWorld()->SpawnActor(BPProject0ActorClass));

	// GetWorld()->DestroyActor(AProject0Actor);

	Project0Actor->SetLifeSpan(5.0f);
}

// Called every frame
void AMainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

