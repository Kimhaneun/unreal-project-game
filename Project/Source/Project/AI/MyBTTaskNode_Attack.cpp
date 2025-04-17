// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyBTTaskNode_Attack.h"
#include "AIController.h"
#include "Interface/Project0AIInterface.h"

UMyBTTaskNode_Attack::UMyBTTaskNode_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UMyBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	IProject0AIInterface* Project0AIPawn = Cast<IProject0AIInterface>(ControllingPawn);
	if (Project0AIPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}


	FAIAttackFinished OnAttackFinished;
	OnAttackFinished.BindLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);

	Project0AIPawn->SetAIAttackFinishedDelegate(OnAttackFinished);
	Project0AIPawn->AttackByAI();
	return EBTNodeResult::InProgress;
}
