// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Project0PlayerHUDWidget.h"
#include "UI/Project0HPBarWidget.h"
#include "UI/Project0CharacterStatWidget.h"

UProject0PlayerHUDWidget::UProject0PlayerHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UProject0PlayerHUDWidget::UpdateStat(const FProject0CharacterStat& BaseStat, const FProject0CharacterStat& ModifierStat) 
{
	WidgetHPBar->UpdateStat(BaseStat, ModifierStat);
	WidgetCharacterStat->UpdateStat(BaseStat, ModifierStat);

}

void UProject0PlayerHUDWidget::UpdateHP(float NewCurrentHP)
{
	WidgetHPBar->UpdateHP(NewCurrentHP);
}
