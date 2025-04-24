// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Project0CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Project/Character/Project0ComboAttackData.h"
#include "Engine/DamageEvents.h"
#include "CharacterStat/project0CharacterComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Project0HPBarWidget.h"

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
					
	// Animation
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRefernce(TEXT("/Script/Engine.AnimBlueprint'/Game/04Animation/ABP_Player.ABP_Player_C'"));
	if (AnimInstanceRefernce.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimInstanceRefernce.Class);

	// Stat component
	StatComponent = CreateDefaultSubobject<UProject0CharacterComponent>(TEXT("Stat"));

	// HP Bar Widget Component
	HPBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidgetComponent->SetupAttachment(GetRootComponent());
	HPBarWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget> HPBarWidgetReference(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_HPBar.WBP_HPBar_C'"));
	if (HPBarWidgetReference.Succeeded())
	{
		HPBarWidgetComponent->SetWidgetClass(HPBarWidgetReference.Class);
		HPBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		HPBarWidgetComponent->SetDrawSize(FVector2D(150.0f, 15.0f));
		HPBarWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

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

	// Dead Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageReference(TEXT("/Script/Engine.AnimMontage'/Game/04Animation/AM_Dead.AM_Dead'"));
	if (DeadMontageReference.Succeeded())
	{
		DeadMontage = DeadMontageReference.Object;
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
	StatComponent->OnHpZeroDelegate.AddUObject(this, &AProject0CharacterBase::SetDead);
}

void AProject0CharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StatComponent->OnHpZeroDelegate.AddUObject(this, &AProject0CharacterBase::SetDead);
	StatComponent->OnStatChangedDelegage.AddUObject(this, &AProject0CharacterBase::ApplyStat);

	if (HPBarWidgetComponent == nullptr)
	{
		return;
	}

	HPBarWidgetComponent->InitWidget();
	UProject0HPBarWidget* HPBarWidget = Cast<UProject0HPBarWidget>(HPBarWidgetComponent->GetUserWidgetObject());
	if (HPBarWidget)
	{
		HPBarWidget->UpdateStat(StatComponent->GetBaseStat(), StatComponent->GetModifierStat());
		HPBarWidget->UpdateHP(StatComponent->GetCurrentHP());

		StatComponent->OnHpChangedDelegate.AddUObject(HPBarWidget, &UProject0HPBarWidget::UpdateHP);
		StatComponent->OnStatChangedDelegage.AddUObject(HPBarWidget, &UProject0HPBarWidget::UpdateStat);
	}
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

float AProject0CharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	StatComponent->ApplyDamage(DamageAmount);

	return DamageAmount;
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

	const float AttackSpeedRate = StatComponent->GetTotalStat().AttackSpeed;
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

	const float AttackSpeedRate = StatComponent->GetTotalStat().AttackSpeed;;
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

void AProject0CharacterBase::AttackHitCheck()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const float AttackRange = StatComponent->GetTotalStat().AttackRange;
	const float AttackRadius = StatComponent->GetTotalStat().AttackRadius;
	const float AttackDamage = StatComponent->GetTotalStat().Attack;

	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(AttackRadius), Params);

	if (HitDetected)
	{
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);

		UE_LOG(LogTemp, Log, TEXT("Hello, World!"));
	}

#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
#endif
}

void AProject0CharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->StopAllMontages(false);
		AnimInstance->Montage_Play(DeadMontage, 1.0f);
	}

	SetActorEnableCollision(false);

	HPBarWidgetComponent->SetVisibility(false);
}

void AProject0CharacterBase::ApplyStat(const FProject0CharacterStat& BaseStat, const FProject0CharacterStat& ModifierStat)
{
	float MovementSpeed = (BaseStat + ModifierStat).MovementSpeed;
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}
