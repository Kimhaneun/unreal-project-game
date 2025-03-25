// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Project0CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AProject0CharacterBase::AProject0CharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Pawn compoents
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule component
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 88.0f);

	// Movement compoents
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.f, 0.0f));

	// static
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> FindMeshReference(TEXT("/Script/Engine.SkeletalMesh'/Game/02Environment/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));

	if (FindMeshReference.Succeeded())
		GetMesh()->SetSkeletalMesh(FindMeshReference.Object);
}

// Called when the game starts or when spawned
void AProject0CharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProject0CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AProject0CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

