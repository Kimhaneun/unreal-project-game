// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Project0Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AProject0Player::AProject0Player()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 700.0f;

	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Camera->bUsePawnControlRotation = false;
}

void AProject0Player::BeginPlay()
{
	Super::BeginPlay();
}

void AProject0Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProject0Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);	
}
