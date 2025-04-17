// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Project0AIInterface.generated.h"

// 구독자 한 명의 대리자
DECLARE_DELEGATE(FAIAttackFinished);

// 구독자 여러 명의 대리자
// DECLARE_MULTICAST_DELEGATE();

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UProject0AIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_API IProject0AIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual float GetAttackRange() = 0;
	virtual void AttackByAI() = 0;
	virtual void SetAIAttackFinishedDelegate(const FAIAttackFinished&  InOnAttackFinished) = 0;
};
