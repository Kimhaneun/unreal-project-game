// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/Project0AttackInterface.h"
#include "Project0CharacterBase.generated.h"

struct FProject0CharacterStat;

UCLASS()
class PROJECT_API AProject0CharacterBase : public ACharacter, public IProject0AttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProject0CharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual void ProcessAttack();
	virtual void ProcessComboAttack();

	virtual void ComboAttackBegin();
	virtual void ComboAttackEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);

	void SetComboCheckTimer();
	void ComboCheck();

	// IProject0AttackInterface을(를) 통해 상속됨
	void AttackHitCheck() override;

	virtual void SetDead();

	void ApplyStat(const FProject0CharacterStat& BaseStat, const FProject0CharacterStat& ModifierStat);
	FORCEINLINE TObjectPtr<class UProject0CharacterComponent> GetStatComponent() { return StatComponent; }

protected:
	UPROPERTY(EditAnywhere, Category = Attack)
	TObjectPtr<class UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, Category = Attack)
	TObjectPtr<class UAnimMontage> ComboAttackMontage;

	UPROPERTY(EditAnywhere, Category = Attack)
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, Category = Attack)
	TObjectPtr<class  UProject0ComboAttackData> ComboAttackData;

	int32 CurrentCombo = 0;

	FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UProject0CharacterComponent> StatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UWidgetComponent> HPBarWidgetComponent;

	// UWidgetComoponent
};
