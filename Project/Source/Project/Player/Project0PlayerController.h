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
};
