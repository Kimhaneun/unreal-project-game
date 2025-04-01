// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Project0Box.h"

// Sets default values
AProject0Box::AProject0Box()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	SetRootComponent(BoxMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/02Environment/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));
	if (BoxMeshRef.Succeeded())
	{
		BoxMesh->SetStaticMesh(BoxMeshRef.Object);
	}
}

// Called when the game starts or when spawned
void AProject0Box::BeginPlay()
{
	Super::BeginPlay();
	
	BoxMesh->OnComponentHit.AddDynamic(this, &AProject0Box::OnHit);
	BoxMesh->OnComponentBeginOverlap.AddDynamic(this, &AProject0Box::OnBeginOverlap);
}

// Called every frame
void AProject0Box::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProject0Box::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}

void AProject0Box::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Project0_Box Overlap"));
}

