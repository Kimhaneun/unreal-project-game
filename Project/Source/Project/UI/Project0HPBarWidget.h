// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Project0HPBarWidget.generated.h"

struct FProject0CharacterStat;

/**
 * 
 */
UCLASS()
class PROJECT_API UProject0HPBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UProject0HPBarWidget(const FObjectInitializer& ObjectInitializer);

public:
	void UpdateStat(const FProject0CharacterStat& BaseStat, const FProject0CharacterStat& ModifierStat);
	void UpdateHP(float NewCurrentHP);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UProgressBar> HPBar;

	float CurrentHP;
	float MaxHP;

};

