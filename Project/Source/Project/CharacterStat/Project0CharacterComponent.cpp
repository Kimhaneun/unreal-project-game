// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/Project0CharacterComponent.h"
#include "Singleton/Project0GameSingleton.h"

// Sets default values for this component's properties
UProject0CharacterComponent::UProject0CharacterComponent()
{
	CurrentLevel = 1;
	bWantsInitializeComponent = true;
	// ...
}


// Called when the game starts
void UProject0CharacterComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UProject0CharacterComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevel(CurrentLevel);
	SetHP(BaseStat.MaxHP);
}

float UProject0CharacterComponent::ApplyDamage(float InDamage)
{
	const float PreHP = CurrentHP;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0.0f, InDamage);

	SetHP(CurrentHP - ActualDamage);
	if (CurrentHP <= KINDA_SMALL_NUMBER)
	{
		OnHpZeroDelegate.Broadcast();
	}

	return ActualDamage;
}

void UProject0CharacterComponent::SetLevel(int32 NewLevel)
{
	CurrentLevel = FMath::Clamp(NewLevel, 1, UProject0GameSingleton::GetInstance()->GetCharacterMaxLevel());
	SetBaseStat(UProject0GameSingleton::GetInstance()->GetCharacterStat(CurrentLevel));
}

void UProject0CharacterComponent::SetHP(float NewHP)
{
	CurrentHP = FMath::Clamp(NewHP, 0.0f, GetTotalStat().MaxHP);
	OnHpChangedDelegate.Broadcast(CurrentHP);
}