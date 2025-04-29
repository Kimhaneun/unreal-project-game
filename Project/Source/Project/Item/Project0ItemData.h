// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Project0ItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon,
	Potion,
	Scroll
};

/**
 *
 */
UCLASS()
class PROJECT_API UProject0ItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(FName("Project0ItemData"), GetFName());
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EItemType Type;
};
