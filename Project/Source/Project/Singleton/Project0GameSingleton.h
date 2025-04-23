// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Project0GameSingleton.generated.h"

// 전방 선언
struct  FProject0CharacterStat;

/**
 * 
 */
UCLASS()
class PROJECT_API UProject0GameSingleton : public UObject
{
	GENERATED_BODY()

public:
	UProject0GameSingleton();
	static UProject0GameSingleton* GetInstance();
	
public:
	FProject0CharacterStat GetCharacterStat(int32 InLevel) const;
	FORCEINLINE int32 GetCharacterMaxLevel() const { return CharacterMaxLevel; }

private:
	TArray<FProject0CharacterStat> CharacterStatTable;

	UPROPERTY()
	int32 CharacterMaxLevel;
};
