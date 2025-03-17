// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainActor.generated.h"

class project0Actor;

UCLASS()
class PROJECT_API AMainActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
#pragma region Create Project0Actor
	UPROPERTY();
	TObjectPtr<class AProject0Actor> Project0Actor;
#pragma endregion

	// Pointer referring to the class that inherits the  Project0Actor class
	UPROPERTY();
	TSubclassOf<class AProject0Actor> BPProject0ActorClass;
};
