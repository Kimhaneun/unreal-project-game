// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Project0Monster.h"
#include "Components/CapsuleComponent.h"

AProject0Monster::AProject0Monster()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Project0Monster"));

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/02Environment/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));

	if (MeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}
}

void AProject0Monster::BeginPlay()
{
	Super::BeginPlay();
}

void AProject0Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
