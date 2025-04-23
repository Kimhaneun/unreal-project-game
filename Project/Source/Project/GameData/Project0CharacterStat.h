// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Project0CharacterStat.generated.h"

/**
 *
 */
 // BlueprintType: Blueprint에서 해당 구조체를 사용할 수 있게 한다.
USTRUCT(BlueprintType)
struct FProject0CharacterStat : public FTableRowBase
{
	// GENERATED_USTRUCT_BODY: 기존의 Class를 구조체로 생성한다.
	GENERATED_USTRUCT_BODY()

public:
	// 기본 생성자에서 변수를 초기화한다.
	FProject0CharacterStat() : MaxHP(0.0f), Attack(0.0f), AttackRange(0.0f), AttackRadius(0.0f), AttackSpeed(0.0f), MovementSpeed(0.0f) {}

public:
	// 구조체를 더하는 연산자
	FProject0CharacterStat operator+(const FProject0CharacterStat& Other) const
	{
		// 내 구조체의 포인터를 float형 포인터로 변환하여 사용한다.
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);

		// 상대 구조체의 포인터를 float형 포인터로 변환하여 사용한다.
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FProject0CharacterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);

		int32 StatNumber = sizeof(FProject0CharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatNumber; ++i)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}
		return Result;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MovementSpeed;


};
