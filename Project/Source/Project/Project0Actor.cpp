// Fill out your copyright notice in the Description page of Project Settings.


#include "Project0Actor.h"
#include "Project0Object.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AProject0Actor::AProject0Actor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 이러면 안 될 거 아는데 너 앞에만 서면 나락

	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetRelativeScale3D(FVector(4.0f, 1.0f, 0.5f));



	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	Head->SetupAttachment(Box);
	Head->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));
	Head->SetRelativeScale3D(FVector(0.1875f, 0.5f, 1.5f));



	Wing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wing"));
	Wing->SetupAttachment(Wing);
	Wing->SetRelativeLocation(FVector(17.5f, 0.0f, 0.0f));
	Wing->SetRelativeScale3D(FVector(0.25f, 3.5f, 0.5f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> FindMeshReference(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	if (FindMeshReference.Succeeded())
	{
		Box->SetStaticMesh(FindMeshReference.Object);
		Head->SetStaticMesh(FindMeshReference.Object);
		Wing->SetStaticMesh(FindMeshReference.Object);
	}
}

// Called when the game starts or when spawned
void AProject0Actor::BeginPlay()
{
	Super::BeginPlay();

	// object = NewObject<UProject0Object>();

	// GarbageCollection forced execution
	GEngine->ForceGarbageCollection(true);
}

// Called every frame
void AProject0Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	// if (object == nullptr)
	// 	UE_LOG(LogTemp, Log, TEXT("object nullptr."));



	float MovementSpeed = 50.0f;
	float Distance = DeltaTime * MovementSpeed;

	FVector Location = GetActorLocation();
	FVector NewLocation = Location + FVector::ForwardVector * Distance;

	SetActorLocation(NewLocation);



	AddActorWorldOffset(FVector::ForwardVector);

	float RotationRate = 45.0f;
	FRotator Rotation = GetActorRotation();
	FRotator NewRotation = FRotator(Rotation.Pitch, Rotation.Yaw + RotationRate * DeltaTime, Rotation.Roll);

	SetActorRotation(NewRotation);



	AddActorWorldRotation(FRotator(0.0f, RotationRate * DeltaTime, 0.0f));
}

