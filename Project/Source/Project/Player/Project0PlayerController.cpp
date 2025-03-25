// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Project0PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"	

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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ThisClass::InputJump);
	}
}

void AProject0PlayerController::InputAttack(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Blue, TEXT("Attack"));
}

void AProject0PlayerController::InputMovement(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

#pragma region Project0 PlayerController Movement
	// if (MovementVector.X != 0)
	// {
	// 	FVector Direction = GetPawn()->GetActorForwardVector() * MovementVector.X;
	// 	GetPawn()->AddActorWorldOffset(Direction);
	// }
	// 
	// if (MovementVector.Y != 0)
	// {
	// 	FVector Direction = GetPawn()->GetActorRightVector() * MovementVector.Y;
	// 	GetPawn()->AddActorWorldOffset(Direction);
	// }
#pragma endregion

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.X);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.Y);
}

void AProject0PlayerController::InputTurn(const FInputActionValue& InputValue)
{
	float XValue = InputValue.Get<float>();

	AddYawInput(XValue);

	// GetPawn()->AddControllerYawInput(XValue);	

#pragma region Project0 PlayerController Movement
	FRotator Rotation(0.0f, XValue, 0.0f);
	GetPawn()->AddActorLocalRotation(Rotation);
#pragma endregion
}

void AProject0PlayerController::InputJump(const FInputActionValue& InputValue)
{
	ACharacter* Project0Character = Cast<ACharacter>(GetPawn());

	if (Project0Character)
	{
		Project0Character->Jump();
	}
}