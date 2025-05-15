// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/Project0GameInterface.h"
#include "Project0GameMode.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_API AProject0GameMode : public AGameModeBase, public IProject0GameInterface
{
	GENERATED_BODY()

public:
	AProject0GameMode();

public:
	virtual void OnPlayerScoreChanged(int32 NewPlayerScore) override;
	virtual void AddPlayerScore(int32 AddPayerScore) override;
	virtual void OnPlayerDead() override;
	virtual bool IsGameCleared() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ClearScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 bIsCleared : 1;

};
