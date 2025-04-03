// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackHitCheck.h"
#include "AnimNotify_AttackHitCheck.h"
#include "Interface/Project0AttackInterface.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	// AttackHitCheck를 소유한 컴포넌트를 찾을 수 있다.
	if (MeshComp->GetOwner())
	{
		// C++의 인터페이스
		// virtual void 함수() = 0;

		// 주인공 캐릭터에서 충돌을 판정한다.
		IProject0AttackInterface* AttackInterface = Cast<IProject0AttackInterface>(MeshComp->GetOwner());
		if (AttackInterface)
		{
			AttackInterface->AttackHitCheck();
		}
	}
}
