// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Project0Monster.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Project/AI/Project0AIController.h"
#include "Engine/AssetManager.h"

AProject0Monster::AProject0Monster()
{
	AIControllerClass = AProject0AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Project0Monster"));

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetHiddenInGame(true);

	// 이제 다양한 종류의 몬스터를 생성하므로 제거한다.
	// static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/02Environment/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
	// 
	// if (MeshRef.Succeeded())
	// {
	// 	GetMesh()->SetSkeletalMesh(MeshRef.Object);
	// }
}

void AProject0Monster::BeginPlay()
{
	Super::BeginPlay();
}

void AProject0Monster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ensure(MonsterMeshes.Num() > 0);
	int32 RandomIndex = FMath::RandRange(0, MonsterMeshes.Num() - 1);

	MonsterMeshHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(MonsterMeshes[RandomIndex], FStreamableDelegate::CreateUObject(this, &AProject0Monster::MonsterMeshLoadComplete));
}

void AProject0Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProject0Monster::SetDead()
{
	Super::SetDead();

	AProject0AIController* AIController = Cast<AProject0AIController>(GetController());\
		if (AIController)
		{
			AIController->StopAI();
		}

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([&]() {Destroy(); }), DeadEventDelayTime, false);
}

float AProject0Monster::GetAttackRange()
{
	return 150.0f;
}

void AProject0Monster::AttackByAI()
{
	ProcessComboAttack();
}

void AProject0Monster::ComboAttackEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	Super::ComboAttackEnd(TargetMontage, IsProperlyEnded);

	// AttackTask에게 공격이 끝났음을 알림
	OnAttackFinished.ExecuteIfBound();
}

void AProject0Monster::SetAIAttackFinishedDelegate(const FAIAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AProject0Monster::MonsterMeshLoadComplete()
{
	if (MonsterMeshHandle.IsValid())
	{
		USkeletalMesh* MonsterMesh = Cast<USkeletalMesh>(MonsterMeshHandle->GetLoadedAsset());
		if (MonsterMesh)
		{
			GetMesh()->SetSkeletalMesh(MonsterMesh);
			GetMesh()->SetHiddenInGame(false);
		}
	}

	MonsterMeshHandle->ReleaseHandle();
}
