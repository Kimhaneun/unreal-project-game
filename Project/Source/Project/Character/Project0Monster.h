// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Project0CharacterBase.h"
#include "Project0Monster.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AProject0Monster : public AProject0CharacterBase
{
	GENERATED_BODY()
	
public:
	AProject0Monster();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetDead() override;

protected:
	float DeadEventDelayTime = 5.0f;
};
