// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Project0CharacterStatWidget.h"
#include "GameData/Project0CharacterStat.h"
#include "Components/TextBlock.h"

UProject0CharacterStatWidget::UProject0CharacterStatWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UProject0CharacterStatWidget::UpdateStat(const FProject0CharacterStat& BaseStat, const FProject0CharacterStat& ModifierStat)
{
	MaxHPBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.MaxHP)));
	AttackBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.Attack)));
	AttackRangeBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.AttackRange)));
	AttackRadiusBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.AttackRadius)));
	AttackSpeedBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.AttackSpeed)));
	MovementSpeedBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.MovementSpeed)));

	MaxHPModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.MaxHP)));
	AttackModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.Attack)));
	AttackRangeModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.AttackRange)));
	AttackRadiusModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.AttackRadius)));
	AttackSpeedModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.AttackSpeed)));
	MovementSpeedModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.MovementSpeed)));
}