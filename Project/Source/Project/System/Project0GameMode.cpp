// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Project0GameMode.h"
#include "Player/Project0PlayerController.h"

AProject0GameMode::AProject0GameMode()
{
	ClearScore = 3;
	CurrentScore = 0;
	bIsCleared = false;
}

void AProject0GameMode::OnPlayerScoreChanged(int32 NewPlayerScore)
{
	CurrentScore = NewPlayerScore;

	// UI 갱신 작업
	AProject0PlayerController* PlayerController = Cast<AProject0PlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		PlayerController->GameScoreChanged(CurrentScore);
	}
	//

	if (CurrentScore >= ClearScore)
	{
		bIsCleared = true;

		if (PlayerController)
		{
			PlayerController->GameClear();
		}
	}
}

void AProject0GameMode::AddPlayerScore(int32 AddPayerScore)
{
	CurrentScore += AddPayerScore;

	// UI 갱신 작업
	AProject0PlayerController* PlayerController = Cast<AProject0PlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		PlayerController->GameScoreChanged(CurrentScore);
	}
	//

	if (CurrentScore >= ClearScore)
	{
		bIsCleared = true;

		if (PlayerController)
		{
			PlayerController->GameClear();
		}
	}
}

void AProject0GameMode::OnPlayerDead()
{
	AProject0PlayerController* PlayerController = Cast<AProject0PlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		PlayerController->GameOver();
	}
}

bool AProject0GameMode::IsGameCleared()
{
	return bIsCleared;
}
