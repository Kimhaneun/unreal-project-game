// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Project0ItemData.h"
#include "GameData/Project0CharacterStat.h"
#include "Project0WeaponItemData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UProject0WeaponItemData : public UProject0ItemData
{
	GENERATED_BODY()
	
public:
	UProject0WeaponItemData()
	{
		Type = EItemType::Weapon;
	}

public:
	UPROPERTY(EditAnywhere, Category = Weapon)
	TObjectPtr<class USkeletalMesh> WeaponMesh;

	UPROPERTY(EditAnywhere, Category = Weapon)
	FProject0CharacterStat ModifierStat;
};
