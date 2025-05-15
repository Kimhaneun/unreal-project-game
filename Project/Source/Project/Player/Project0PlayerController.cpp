// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Project0PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameData/Project0SaveGame.h"

AProject0PlayerController::AProject0PlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AProject0PlayerController::BeginPlay()
{
	Super::BeginPlay();

	SaveGameInstance = Cast<UProject0SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Player0"), 0));
	if (SaveGameInstance == nullptr)
	{
		SaveGameInstance = NewObject<UProject0SaveGame>();
		SaveGameInstance->RetryCount = 0;
	}
	else 
	{
		SaveGameInstance->RetryCount++;
	}

	K2_OnGameRetryCount(SaveGameInstance->RetryCount);

	// 기존의 마우스 클릭이 있어야 게임이 시작되던 상황에서,
	// 마우스 클릭 없이 게임이 시작되도록 한다.
	// (UI가 발생하면 UI 모드로 변경하는 등의 작업을 할 수 있다.)
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}

void AProject0PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}	

void AProject0PlayerController::GameScoreChanged(int32 NewScore)
{
	K2_OnScoreChanged(NewScore);
}

void AProject0PlayerController::GameClear()
{
	K2_OnGameClear();

	if (SaveGameInstance)
	{
		SaveGameInstance->RetryCount = 0;
		if (!UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Player0"), 0)) 
		{
			UE_LOG(LogTemp, Error, TEXT("Save Game Error!"));
		}
	}
}

void AProject0PlayerController::GameOver()
{
	K2_OnGameOver();

	if (!UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Player0"), 0))
	{
		UE_LOG(LogTemp, Error, TEXT("Save Game Error!"));
	}

	K2_OnGameRetryCount(SaveGameInstance->RetryCount);
}
