// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/Project0ItemInterface.h"
#include "Interface/Project0AttackInterface.h"
#include "Item/Project0ItemData.h"
#include "Project0CharacterBase.generated.h"

struct FProject0CharacterStat;

DECLARE_DELEGATE_OneParam(FOnTakeItemDelegate, class UProject0ItemData* /*InItemData*/)

UCLASS()
class PROJECT_API AProject0CharacterBase : public ACharacter, public IProject0AttackInterface, public IProject0ItemInterface
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

	// Inherited via IProject0ItemInterface
	virtual void TakeItem(UProject0ItemData* InItemData) override;
	virtual void EquipWeapon(UProject0ItemData* InItemData);
	virtual void DrinkPotion(UProject0ItemData* InItemData);
	virtual void ReadScroll(UProject0ItemData* InItemData);

public:
	int32 GetLevel();
	void SetLevel(int32 InNewLevel);

protected:
	TMap<EItemType, FOnTakeItemDelegate> TakeItemActions;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> WeaponComponent;

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

};
