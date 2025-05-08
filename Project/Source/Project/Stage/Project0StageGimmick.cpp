// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage/Project0StageGimmick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/OverlapResult.h"

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

}

void AProject0StageGimmick::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetState(CurrentState);
}

void AProject0StageGimmick::OnStageTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
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
		AProject0StageGimmick* NewGimmick = GetWorld()->SpawnActor<AProject0StageGimmick>(AProject0StageGimmick::StaticClass(), NewTransform);
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
}

void AProject0StageGimmick::SetFight()
{
}

void AProject0StageGimmick::SetChooseReward()
{
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
