// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/Project0CharacterStat.h"
#include "Project0CharacterComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHP*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegage, const FProject0CharacterStat& /*BaseStat*/, const FProject0CharacterStat& /*ModifierStat*/ );

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UProject0CharacterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProject0CharacterComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:
	float ApplyDamage(float InDamage);

public:
	FORCEINLINE float GetCurretLevel() const { return CurrentLevel; }
	FORCEINLINE float GetCurrentHP() const { return CurrentHP; }

	FORCEINLINE const FProject0CharacterStat& GetBaseStat(){ return BaseStat; }
	FORCEINLINE const FProject0CharacterStat& GetModifierStat() { return ModifierStat; }
	FORCEINLINE  FProject0CharacterStat GetTotalStat() const { return BaseStat + ModifierStat; }

public:
	void SetLevel(int32 InLevel);
	void SetHP(float InHP);

	FORCEINLINE void SetBaseStat(const FProject0CharacterStat& InBaseStat) 
	{ 
		BaseStat = InBaseStat; 
		OnStatChangedDelegage.Broadcast(GetBaseStat(), GetModifierStat());
	}

	FORCEINLINE void SetModifierStat(const FProject0CharacterStat& InModifierStat)
	{
		ModifierStat = InModifierStat;
		OnStatChangedDelegage.Broadcast(GetBaseStat(), GetModifierStat());

	}

	FORCEINLINE void AddBaseStat(const FProject0CharacterStat& InAddBassStat)
	{
		BaseStat = BaseStat + InAddBassStat;
		OnStatChangedDelegage.Broadcast(GetBaseStat(), GetModifierStat());
	}

	FORCEINLINE void AddModifierStat(const FProject0CharacterStat& InAddModifierStat)
	{
		ModifierStat = ModifierStat + InAddModifierStat;
		OnStatChangedDelegage.Broadcast(GetBaseStat(), GetModifierStat());
	}

public:
	FOnHpZeroDelegate OnHpZeroDelegate;
	FOnHpChangedDelegate OnHpChangedDelegate;
	FOnStatChangedDelegage OnStatChangedDelegage;

protected:
	UPROPERTY(VisibleAnywhere, Category = Stat)
	float CurrentLevel;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float CurrentHP;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	FProject0CharacterStat BaseStat;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	FProject0CharacterStat ModifierStat;
};