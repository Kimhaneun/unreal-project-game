// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Project0PlayerController.generated.h"

struct FInputActionValue;

/**
 *
 */
UCLASS()
class PROJECT_API AProject0PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AProject0PlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void InputAttack(const FInputActionValue& InputValue);
	void InputMovement(const FInputActionValue& InputValue);
	void InputTurn(const FInputActionValue& InputValue);
	void InputJump(const FInputActionValue& InputValue);

protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MovementAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> TurnAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> JumpAction;
};
