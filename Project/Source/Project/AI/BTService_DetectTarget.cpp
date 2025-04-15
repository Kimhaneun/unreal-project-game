// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_DetectTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/OverlapResult.h"
#include "DrawDebugHelpers.h"

UBTService_DetectTarget::UBTService_DetectTarget()
{
	NodeName = TEXT("Detect");
	Interval = 0.5f;
}

void UBTService_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (Pawn == nullptr)
	{
		return;
	}

	UWorld* World = Pawn->GetWorld();
	if (World == nullptr)
	{
		return;
	}

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionParams;	
	CollisionParams.AddIgnoredActor(Pawn);

	FVector Location = Pawn->GetActorLocation();

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(DetectionRadius),
		CollisionParams
	);

	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			APawn* TargetPawn = Cast<APawn>(OverlapResult.GetActor());
			if (TargetPawn && TargetPawn->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), TargetPawn);

				DrawDebugSphere(
					World,
					Location,
					DetectionRadius,
					16,
					FColor::Green,
					false,
					0.2f
				);

				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), nullptr);

	DrawDebugSphere(
		World,
		Location,
		DetectionRadius,
		16,
		FColor::Red,
		false,
		0.2f
	);
}
