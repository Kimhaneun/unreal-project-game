// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Project0PlayerController.generated.h"

struct FInputActionValue;
/**
 *
 */
UCLASS()
class PROJECT_API AProject0PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AProject0PlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	// BlueprintImplementableEvent: 추상(abstract)
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnScoreChangedCpp"))
	void K2_OnScoreChanged(int32 NewScore);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnGameClearCpp"))
	void K2_OnGameClear();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnGameOverCpp"))
	void K2_OnGameOver();

	UFUNCTION(BlueprintImplementableEvent, Category = "Game", meta = (DisplayName = "OnGameRetryCountCpp"))
	void K2_OnGameRetryCount(int32 NewRetryCount);

public:
	void GameScoreChanged(int32 NewScore);
	void GameClear();
	void GameOver();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SaveGame)
	TObjectPtr< class UProject0SaveGame> SaveGameInstance;

};
