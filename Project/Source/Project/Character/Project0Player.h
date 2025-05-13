// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Project0CharacterBase.h"
#include "Project0Player.generated.h"

struct FInputActionValue;
/**
 *
 */
UCLASS()
class PROJECT_API AProject0Player : public AProject0CharacterBase
{
	GENERATED_BODY()

public:
	AProject0Player();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void SetDead() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = HUD)
	TSubclassOf<class UProject0PlayerHUDWidget> PlayerHUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	TObjectPtr<class UProject0PlayerHUDWidget> PlayerHUDWidget;

#pragma region INPUT SYSTEM
private:
	void InputAttack(const FInputActionValue& InputValue);
	void InputMovement(const FInputActionValue& InputValue);
	void InputTurn(const FInputActionValue& InputValue);
	// void InputJump(const FInputActionValue& InputValue);

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
#pragma endregion

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;
};
