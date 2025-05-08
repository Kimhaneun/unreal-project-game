// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Project0StageGimmick.generated.h"

UENUM(BlueprintType)
enum class EStageState : uint8
{
	Ready = 0,
	Fight,
	Reward,
	Next 
};

DECLARE_DELEGATE(FOnStateChangedDelegate)

UCLASS()
class PROJECT_API AProject0StageGimmick : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProject0StageGimmick();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

#pragma region STAGE
public:
	UFUNCTION()
	void OnStageTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleAnywhere, Category = Stage)
	TObjectPtr<class UStaticMeshComponent> StageMesh;

	UPROPERTY(VisibleAnywhere, Category = Stage)
	TObjectPtr<class UBoxComponent> StageTriggerBox;

#pragma endregion

#pragma region GATE
public:
	UFUNCTION()
	void OnGateTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OpenAllGates();
	void CloseAllGates();

protected:
	UPROPERTY(VisibleAnywhere, Category = Gate)
	TMap<FName, TObjectPtr<class UStaticMeshComponent>> GateMeshes;

	UPROPERTY(VisibleAnywhere, Category = Gate)
	TArray<TObjectPtr<class UBoxComponent>> GateTriggerBoxes;

#pragma endregion

#pragma region GAME STATE
public:
	void SetState(EStageState InNewState);
	void SetReady();
	void SetFight();
	void SetChooseReward();
	void SetChooseNext();

protected:
	UPROPERTY(EditAnywhere, Category = Stage)
	EStageState CurrentState;

	TMap<EStageState, FOnStateChangedDelegate> StateChangedDelegates;
#pragma endregion

};
