// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Project0CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Project/Character/Project0ComboAttackData.h"

// Sets default values
AProject0CharacterBase::AProject0CharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Pawn compoents
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule component
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 88.0f);

	// Movement compoents
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.f, 0.0f));

	// static
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> FindMeshReference(TEXT("/Script/Engine.SkeletalMesh'/Game/02Environment/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));

	if (FindMeshReference.Succeeded())
		GetMesh()->SetSkeletalMesh(FindMeshReference.Object);

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRefernce(TEXT("/Script/Engine.AnimBlueprint'/Game/04Animation/ABP_Player.ABP_Player_C'"));
	if (AnimInstanceRefernce.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimInstanceRefernce.Class);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageReference(TEXT("/Script/Engine.AnimMontage'/Game/04Animation/AM_Attack.AM_Attack'"));
	if (AttackMontageReference.Succeeded())
	{
		AttackMontage = AttackMontageReference.Object;
	}

	// Combo Attack Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboAttackMontageReference(TEXT("/Script/Engine.AnimMontage'/Game/04Animation/AM_ComboAttack.AM_ComboAttack'"));
	if (ComboAttackMontageReference.Succeeded())
	{
		ComboAttackMontage = ComboAttackMontageReference.Object;
	}

	// Combo Attack Data
	static ConstructorHelpers::FObjectFinder<UProject0ComboAttackData> ComboAttackDataReference(TEXT("/Script/Project.Project0ComboAttackData'/Game/05CharacterAction/DA_ComboAttackData.DA_ComboAttackData'"));
	if (ComboAttackDataReference.Succeeded())
	{
		ComboAttackData = ComboAttackDataReference.Object;
	}
}

// Called when the game starts or when spawned
void AProject0CharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProject0CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AProject0CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AProject0CharacterBase::ProcessAttack()
{
	if (GetCurrentMontage() == AttackMontage)
		return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		int32 Index = FMath::RandRange(1, 4);
		FString SectionName = FString::Printf(TEXT("Attack%d"), Index);

		AnimInstance->Montage_Play(AttackMontage, 1.0f);
		AnimInstance->Montage_JumpToSection(FName(*SectionName));
	}
}

void AProject0CharacterBase::ProcessComboAttack()
{
#pragma region COMBO ATTACK
	if (CurrentCombo == 0)
	{
		ComboAttackBegin();
		return;
	}

	if (ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = true;
	}
	else
	{
		HasNextComboCommand = false;
	}
#pragma endregion

	// UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	// if (AnimInstance)
	// {
	// 	AnimInstance->Montage_Play(ComboAttackMontage, 1.0f);
	// }
}

void AProject0CharacterBase::ComboAttackBegin()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	// Combo Attack Start
	CurrentCombo = 1;

	const float AttackSpeedRate = 1.0f;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboAttackMontage, AttackSpeedRate);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &AProject0CharacterBase::ComboAttackEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboAttackMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void AProject0CharacterBase::ComboAttackEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	CurrentCombo = 0;
}

void AProject0CharacterBase::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;

	const float AttackSpeedRate = 1.0f;
	float ComboEffectiveTime = (ComboAttackData->EffectiveFrameCount[ComboIndex] / ComboAttackData->FrameRate) / AttackSpeedRate;

	if (ComboEffectiveTime > 0.0f)
	{
		GetWorldTimerManager().SetTimer(ComboTimerHandle, this, &AProject0CharacterBase::ComboCheck, ComboEffectiveTime, false);
	}
}

void AProject0CharacterBase::ComboCheck()
{
	ComboTimerHandle.Invalidate();

	if (HasNextComboCommand)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboAttackData->MaxComboCount);

		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboAttackData->MontageSectionNamePrefix, CurrentCombo);

		AnimInstance->Montage_JumpToSection(NextSection, ComboAttackMontage);

		SetComboCheckTimer();
		HasNextComboCommand = false;
	}
}
