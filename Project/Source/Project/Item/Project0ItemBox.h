// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Project0ItemBox.generated.h"

UCLASS()
class PROJECT_API AProject0ItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProject0ItemBox();

protected:
	// PostInitializeComponents(): Awake()함수와 같은 동작을 한다.
	virtual void PostInitializeComponents() override;

public:
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEffectFinished(class UParticleSystemComponent* PSystem);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UBoxComponent> TriggerBox;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UParticleSystemComponent> Effect;

	// 최소 단위를 가져야 확장성이 높다.
	UPROPERTY(EditAnywhere, Category = Item)
	TObjectPtr<class UProject0ItemData> ItemData;

};
