// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Project0ItemData.h"
#include "GameData/Project0CharacterStat.h"
#include "Project0ScrollItemData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UProject0ScrollItemData : public UProject0ItemData
{
	GENERATED_BODY()
	
public:
	UProject0ScrollItemData()
	{
		Type = EItemType::Scroll;
	}

public:
	UPROPERTY(EditAnywhere, Category = Scroll)
	FProject0CharacterStat BaseStat;
};