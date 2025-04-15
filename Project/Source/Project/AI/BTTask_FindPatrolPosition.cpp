// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindPatrolPosition.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPatrolPosition::UBTTask_FindPatrolPosition()
{
	NodeName = TEXT("FindPatrolPosition");
}

EBTNodeResult::Type UBTTask_FindPatrolPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
#pragma region 폰 예외 처리
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::Failed)
	{
		return EBTNodeResult::Failed;
	}

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
#pragma endregion

#pragma region 네부메쉬 예외 처리 
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (NavSystem == nullptr)
	{
		return EBTNodeResult::Failed;
	}
#pragma endregion

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("HomePosition"));
	FNavLocation NextPatrolLocation;

	if (NavSystem->GetRandomPointInNavigableRadius(Origin, PatrolRadius, NextPatrolLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPosition"), NextPatrolLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
	
}
