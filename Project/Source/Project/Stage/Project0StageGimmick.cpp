// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage/Project0StageGimmick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/OverlapResult.h"
#include "Character/Project0Monster.h"
#include "Item/Project0ItemBox.h"

// Sets default values
AProject0StageGimmick::AProject0StageGimmick()
{
	StageMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StageMesh"));
	SetRootComponent(StageMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StageMeshReference(TEXT("/Script/Engine.StaticMesh'/Game/02Environment/Environment/Stages/SM_SQUARE.SM_SQUARE'"));
	if (StageMeshReference.Succeeded())
	{
		StageMesh->SetStaticMesh(StageMeshReference.Object);
	}

	StageTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("StageTriggerBox"));


	StageTriggerBox->SetupAttachment(GetRootComponent());
	StageTriggerBox->SetBoxExtent(FVector(775.0f, 775.0f, 300.0f));
	StageTriggerBox->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	StageTriggerBox->SetCollisionProfileName(FName("Project0Trigger"));
	StageTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AProject0StageGimmick::OnStageTriggerBoxBeginOverlap);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> GateMeshReference(TEXT("/Script/Engine.StaticMesh'/Game/02Environment/Environment/Props/SM_GATE.SM_GATE'"));
	if (!GateMeshReference.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load GateMeshReference"));
	}

	static FName GateSockets[] = { TEXT("+XGate"), TEXT("-XGate"), TEXT("+YGate"), TEXT("-YGate") };
	for (FName GateSocket : GateSockets)
	{
		UStaticMeshComponent* GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(GateSocket);
		GateMesh->SetStaticMesh(GateMeshReference.Object);
		GateMesh->SetupAttachment(StageMesh, GateSocket);
		GateMesh->SetRelativeLocation(FVector(0.0f, -80.0f, 0.0f));
		GateMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

		GateMeshes.Add(GateSocket, GateMesh);

		FName TriggerBoxName = *GateSocket.ToString().Append(TEXT("TriggerBox"));
		UBoxComponent* GateTriggerBox = CreateDefaultSubobject<UBoxComponent>(TriggerBoxName);
		GateTriggerBox->SetupAttachment(StageMesh, GateSocket);
		GateTriggerBox->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));
		GateTriggerBox->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
		GateTriggerBox->SetCollisionProfileName(FName("Project0Trigger"));
		GateTriggerBox->ComponentTags.Add(GateSocket);
		GateTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AProject0StageGimmick::OnGateTriggerBoxBeginOverlap);
		GateTriggerBoxes.Add(GateTriggerBox);
	}

	// Game State
	CurrentState = EStageState::Ready;

	StateChangedDelegates.Add(EStageState::Ready, FOnStateChangedDelegate::CreateUObject(this, &AProject0StageGimmick::SetReady));
	StateChangedDelegates.Add(EStageState::Fight, FOnStateChangedDelegate::CreateUObject(this, &AProject0StageGimmick::SetFight));
	StateChangedDelegates.Add(EStageState::Reward, FOnStateChangedDelegate::CreateUObject(this, &AProject0StageGimmick::SetChooseReward));
	StateChangedDelegates.Add(EStageState::Next, FOnStateChangedDelegate::CreateUObject(this, &AProject0StageGimmick::SetChooseNext));

	// Fight State
	// 블루프린트 클래스는 인스턴스화 하기 위해 생성자에서 선언하는것이 좋다.
	static ConstructorHelpers::FClassFinder<AProject0Monster> MonsterReference(TEXT("/Script/Engine.Blueprint'/Game/01BluePrints/BP_Project0Monster.BP_Project0Monster_C'"));
	if (StageMeshReference.Succeeded())
	{
		MonsterClass = MonsterReference.Class;
	}

	// Reward State
	static FName RewardSockets[] = { TEXT("+XReward"), TEXT("-XReward"), TEXT("+YReward"), TEXT("-YReward") };

	for (FName RewardSocket : RewardSockets)
	{
		// Item Box를 생성할 위치를 생성한다.
		FVector BoxLocation = StageMesh->GetSocketLocation(RewardSocket);
		RewardBoxLocations.Add(RewardSocket, BoxLocation);
	}
}

void AProject0StageGimmick::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetState(CurrentState);
}

void AProject0StageGimmick::OnStageTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetState(EStageState::Fight);
}

void AProject0StageGimmick::OnGateTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	check(OverlappedComponent->ComponentTags.Num() == 1);
	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	FName SocketName = FName(*ComponentTag.ToString().Left(2));
	check(StageMesh->DoesSocketExist(SocketName));

	FVector NewLocation = StageMesh->GetSocketLocation(SocketName);
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);

	bool bResult = GetWorld()->OverlapMultiByObjectType(OverlapResults, NewLocation, FQuat::Identity, FCollisionObjectQueryParams::InitType::AllObjects, FCollisionShape::MakeSphere(775.0f), CollisionQueryParams);

	if (!bResult)
	{
		FTransform NewTransform(NewLocation);
		AProject0StageGimmick* NewGimmick = GetWorld()->SpawnActorDeferred<AProject0StageGimmick>(AProject0StageGimmick::StaticClass(), NewTransform);

		if (NewGimmick)
		{
			NewGimmick->SetStageLevel(CurrentStageLevel + 1);
			NewGimmick->FinishSpawning(NewTransform);
		}
	}
}

void AProject0StageGimmick::OpenAllGates()
{
	for (const auto& GateMesh : GateMeshes)
	{
		GateMesh.Value->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
}

void AProject0StageGimmick::CloseAllGates()
{
	for (const auto& GateMesh : GateMeshes)
	{
		GateMesh.Value->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
}

void AProject0StageGimmick::SetState(EStageState InNewState)
{
	CurrentState = InNewState;

	if (StateChangedDelegates.Contains(CurrentState))
	{
		StateChangedDelegates[CurrentState].ExecuteIfBound();
	}
}

void AProject0StageGimmick::SetReady()
{
	// StageTriggerBox만 활성화 하고, GateTriggerBox는 비활성화한다.
	StageTriggerBox->SetCollisionProfileName(FName("Project0Trigger"));
	for (auto GateTriggerBox : GateTriggerBoxes)
	{
		GateTriggerBox->SetCollisionProfileName(FName("NoCollision"));
	};

	// 모든 Gate 문을 닫는다.
	OpenAllGates();
}

void AProject0StageGimmick::SetFight()
{
	// 모든 충돌 처리를 비활성화 한다.
	StageTriggerBox->SetCollisionProfileName(FName("NoCollision"));
	for (auto GateTriggerBox : GateTriggerBoxes)
	{
		GateTriggerBox->SetCollisionProfileName(FName("NoCollision"));
	};

	// 모든 Gate 문을 닫는다.
	CloseAllGates();

	GetWorld()->GetTimerManager().SetTimer(MonsterSpawnTimerHandle, this, &AProject0StageGimmick::OnMonsterSpawn, MonsterSpawnTime, false);
}

void AProject0StageGimmick::SetChooseReward()
{
	StageTriggerBox->SetCollisionProfileName(FName("NoCollision"));
	for (auto GateTriggerBox : GateTriggerBoxes)
	{
		GateTriggerBox->SetCollisionProfileName(FName("NoCollision"));
	};

	CloseAllGates();

	SpawnRewardBoxes();
}

void AProject0StageGimmick::SetChooseNext()
{
	StageTriggerBox->SetCollisionProfileName(FName("NoCollision"));
	for (auto GateTriggerBox : GateTriggerBoxes)
	{
		GateTriggerBox->SetCollisionProfileName(FName("Project0Trigger"));
	}

	OpenAllGates();
}

void AProject0StageGimmick::OnMonsterSpawn()
{
	// 적을 생성할 때 기본 생성 바닥과 조금 떨어진 거리 + 몬스터의 캡술 중앙 위치를 계산하여 바닥과 떨어져서 생성한다.
	const FTransform SpawnTransform(GetActorLocation() + FVector::UpVector * 88.0f);
	// SpawnActorDeferred: 지연 생성
	AProject0Monster* NewMonster = GetWorld()->SpawnActorDeferred<AProject0Monster>(MonsterClass, SpawnTransform);
	if (NewMonster)
	{
		NewMonster->OnDestroyed.AddDynamic(this, &AProject0StageGimmick::OnMonsterDestroyed);
		NewMonster->SetLevel(CurrentStageLevel);
		NewMonster->FinishSpawning(SpawnTransform);
	}
}

void AProject0StageGimmick::OnMonsterDestroyed(AActor* DestroyedActor)
{
	// 몬스터가 죽으면 실행되는 함수
	SetState(EStageState::Reward);
}

void AProject0StageGimmick::SpawnRewardBoxes()
{
	for (const auto& RewardBoxLocationss : RewardBoxLocations)
	{
		FTransform SpawnTransform(GetActorLocation() + RewardBoxLocationss.Value + FVector(0.0f, 0.0f, 30.0f));
		AProject0ItemBox* RewardBoxActor = GetWorld()->SpawnActorDeferred<AProject0ItemBox>(AProject0ItemBox::StaticClass(), SpawnTransform);

		if (RewardBoxActor)
		{
			RewardBoxActor->Tags.Add(RewardBoxLocationss.Key);
			RewardBoxActor->GetTriggerBox()->OnComponentBeginOverlap.AddDynamic(this, & AProject0StageGimmick::OnRewardBoxBeginOverlap);
			RewardBoxes.Add(RewardBoxActor);
		}
	}

	for (const auto& RewardBox : RewardBoxes)
	{
		if (RewardBox.IsValid())
		{
			RewardBox.Get()->FinishSpawning(RewardBox.Get()->GetActorTransform());
		}
	}
}

void AProject0StageGimmick::OnRewardBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (const auto& RewardBox : RewardBoxes)
	{
		if (RewardBox.IsValid())
		{
			AProject0ItemBox* ValidItemBox = RewardBox.Get();
			AActor* OverlapBox = OverlappedComponent->GetOwner();
			if (OverlapBox != ValidItemBox)
			{
				ValidItemBox->Destroy();
			}
		}
	}

	SetState(EStageState::Next);
}
