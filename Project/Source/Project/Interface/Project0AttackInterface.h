// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Project0AttackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UProject0AttackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

// 실제 인터페이스 구현부 
class PROJECT_API IProject0AttackInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 인터페이스이자 추상 클래스
	// C++에는 인터페이스가 없기 때문에 추상 클래스를 인터페이스처럼 사용한다.
	virtual void AttackHitCheck() = 0;
};
