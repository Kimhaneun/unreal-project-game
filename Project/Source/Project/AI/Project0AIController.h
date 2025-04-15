// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Project0AIController.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_API AProject0AIController : public AAIController
{
	GENERATED_BODY()

public:
	AProject0AIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	void RunAI();
	void StopAI();

protected:
	UPROPERTY(EditAnywhere, Category = AI)
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY(EditAnywhere, Category = AI)
	TObjectPtr<class UBehaviorTree> BTAsset;
};
