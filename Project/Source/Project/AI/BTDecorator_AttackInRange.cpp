// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_AttackInRange.h"
#include "AI/Project0AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/Project0AIInterface.h"

UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
	NodeName = "AttackInRange";
}

bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (Pawn == nullptr)
	{
		return false;
	}

	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));
	if (TargetPawn == nullptr)
	{
		return false;
	}

	IProject0AIInterface* Project0AIPawn = Cast< IProject0AIInterface>(Pawn);
	if (Project0AIPawn)
	{
		return (Pawn)->GetDistanceTo(TargetPawn)<= Project0AIPawn->GetAttackRange();
	}

	return (Pawn->GetDistanceTo(TargetPawn) <= AttackRange);
}
