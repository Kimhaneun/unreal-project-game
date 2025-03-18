// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Project0PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AProject0PlayerController::AProject0PlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AProject0PlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
		Subsystem->AddMappingContext(InputMappingContext, 0);
}

void AProject0PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ThisClass::InputAttack);
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ThisClass::InputMovement);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ThisClass::InputTurn);
	}
}

void AProject0PlayerController::InputAttack(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Blue, TEXT("Attack"));
}

void AProject0PlayerController::InputMovement(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	if (MovementVector.X != 0)
	{
		FVector Direction = GetPawn()->GetActorForwardVector() * MovementVector.X;
		GetPawn()->AddActorWorldOffset(Direction);
	}

	if (MovementVector.Y != 0)
	{
		FVector Direction = GetPawn()->GetActorRightVector() * MovementVector.Y;
		GetPawn()->AddActorWorldOffset(Direction);
	}
}

void AProject0PlayerController::InputTurn(const FInputActionValue& InputValue)
{
	float XValue = InputValue.Get<float>();
	FRotator Rotation(0.0f, XValue, 0.0f);
	GetPawn()->AddActorLocalRotation(Rotation);
}
