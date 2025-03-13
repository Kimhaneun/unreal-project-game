// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Project0Actor.generated.h"

class UProject0Object;
class UStaticMeshComponent;

UCLASS()
class PROJECT_API AProject0Actor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProject0Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> Head;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> Wing;

#pragma region  ACTOR MOVEMENT
	// UPROPERTY(EditAnywherer, Category = Battle)
	// TObjectPtr<AProject0Actor> Target;
#pragma endregion

public:
#pragma region OBJECT CREATE WITH SMART POINTER
	// Transfers management role to Unreal.
	// UPROPERTY()
	// UProject0Object* Object;
#pragma endregion

#pragma region ADDED UPROPERTY VARIABLES
	// UPROPERTY(VisibleAnywhere)
	// int32 HealthPoint = 100;
	// 
	// UPROPERTY(EditAnywhere)
	// int32 ManaPoint = 50;
	// 
	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// float MovementSpeed = 10;
#pragma endregion
};
