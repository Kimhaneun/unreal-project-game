// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Project0PlayerController.h"

AProject0PlayerController::AProject0PlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AProject0PlayerController::BeginPlay()
{
	Super::BeginPlay();

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