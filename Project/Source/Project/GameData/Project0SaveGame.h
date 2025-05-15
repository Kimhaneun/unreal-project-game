// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Project0SaveGame.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_API UProject0SaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UProject0SaveGame();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Game)
	int32 RetryCount;

};
