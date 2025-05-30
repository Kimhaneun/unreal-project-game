// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Project0CharacterBase.h"
#include "Interface/Project0AIInterface.h"
#include "Engine/StreamableManager.h"
#include "Project0Monster.generated.h"

/**
 * 
 */
UCLASS(Config = Monster)
class PROJECT_API AProject0Monster : public AProject0CharacterBase, public IProject0AIInterface
{
	GENERATED_BODY()
	
public:
	AProject0Monster();

protected:
	virtual void BeginPlay() override;

	// PostInitializeComponents(): Awake()함수와 같은 동작을 한다.
	virtual void PostInitializeComponents() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetDead() override;

	// IProject0AIInterface을(를) 통해 상속됨
	virtual float GetAttackRange() override;
	// IProject0AttackInterface을(를) 통해 상속됨
	virtual void AttackByAI() override;
	// IProject0AttackInterface을(를) 통해 상속됨
	virtual void ComboAttackEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded) override;

	// IProject0AIInterface을(를) 통해 상속됨
	virtual void SetAIAttackFinishedDelegate(const FAIAttackFinished& InOnAttackFinished) override;

	void MonsterMeshLoadComplete();

protected:
	float DeadEventDelayTime = 5.0f;

	FAIAttackFinished OnAttackFinished;

protected:
	UPROPERTY(Config)
	TArray<FSoftObjectPath> MonsterMeshes;

	TSharedPtr<FStreamableHandle> MonsterMeshHandle;
};
