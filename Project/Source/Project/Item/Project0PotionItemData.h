// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Project0ItemData.h"
#include "GameData/Project0CharacterStat.h"
#include "Project0PotionItemData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UProject0PotionItemData : public UProject0ItemData
{
	GENERATED_BODY()
	
public:
	UProject0PotionItemData()
	{
		Type = EItemType::Potion;
	}

public:
	UPROPERTY(EditAnywhere, Category = Potion)
	float HealAmount;
};
