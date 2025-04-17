// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_TurnToTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_TurnToTarget::UBTTaskNode_TurnToTarget()
{
	NodeName = TEXT("Turn");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskNode_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::Failed)
	{
		return EBTNodeResult::Failed;
	}

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));
	if (TargetPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector LookVector = TargetPawn->GetActorLocation() - ControllingPawn->GetActorLocation();
	LookVector.Z = 0.0f;
	TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_TurnToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// TickTask() 11 번째 줄의 bNotifyTick = true; 를 통해야 호출할 수 있다.
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	CurrentRot = ControllingPawn->GetActorRotation();
	// DeltaSeconds가 없다면 GetWolrldDeltaSeconds()를 통해서도 가능하다.
	ControllingPawn->SetActorRotation(FMath::RInterpTo(CurrentRot, TargetRot, DeltaSeconds, TurnSpeed));

	if (ControllingPawn->GetActorRotation() == TargetRot)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
