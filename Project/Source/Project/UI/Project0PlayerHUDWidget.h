// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Project0PlayerHUDWidget.generated.h"

struct FProject0CharacterStat;

/**
 * 
 */
UCLASS()
class PROJECT_API UProject0PlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UProject0PlayerHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	void UpdateStat(const FProject0CharacterStat& BaseStat, const FProject0CharacterStat& ModifierStat);
	void UpdateHP(float NewCurrentHP);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UProject0HPBarWidget> WidgetHPBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UProject0CharacterStatWidget> WidgetCharacterStat;

};
