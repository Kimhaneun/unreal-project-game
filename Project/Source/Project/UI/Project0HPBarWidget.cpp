// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Project0HPBarWidget.h"
#include "GameData/Project0CharacterStat.h"
#include "Components/ProgressBar.h"

UProject0HPBarWidget::UProject0HPBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHP = -1.0f;
}

void UProject0HPBarWidget::UpdateStat(const FProject0CharacterStat& BaseStat, const FProject0CharacterStat& ModifierStat)
{
	MaxHP = (BaseStat + ModifierStat).MaxHP;
	if (HPBar)
	{
		HPBar->SetPercent(CurrentHP / MaxHP);
	}
}

void UProject0HPBarWidget::UpdateHP(float NewCurrentHP)
{
	CurrentHP = NewCurrentHP;
	if (HPBar)
	{
		HPBar->SetPercent(CurrentHP / MaxHP);
	}
}
