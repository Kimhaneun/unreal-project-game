// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Project0ItemBox.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Interface/Project0ItemInterface.h"
#include "Engine/AssetManager.h"
#include "Item/Project0ItemData.h"

// Sets default values
AProject0ItemBox::AProject0ItemBox()
{
	// 언리얼 엔진을 활용할 때에는 항상 최적화 작업에 주의하자.

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);
	TriggerBox->SetCollisionProfileName(FName("Project0Trigger"));
	TriggerBox->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	// 방법 1.
	// Mesh->SetupAttachment(TriggerBox);
	
	// 방법 2. 당연히 2가 코드 확장성 면에서 더 좋다.
	Mesh->SetupAttachment(GetRootComponent());

	Mesh->SetCollisionProfileName(FName("NoCollision"));
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));

	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));
	Effect->SetupAttachment(GetRootComponent());
	// OnEnable Start
	Effect->bAutoActivate = false;



	static::ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/02Environment/Environment/Props/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'"));
	if (MeshRef.Succeeded())
	{
		Mesh->SetStaticMesh(MeshRef.Object);
	}

	static::ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/02Environment/Effect/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh'"));
	if (ParticleRef.Succeeded())
	{
		Effect->SetTemplate(ParticleRef.Object);
	}
}

void AProject0ItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AProject0ItemBox::OnBoxBeginOverlap);

	UAssetManager& Manager = UAssetManager::Get();

	TArray<FPrimaryAssetId> Assets;
	Manager.GetPrimaryAssetIdList(TEXT("Project0ItemData"), Assets);
	ensure(Assets.Num() > 0);

	int32 RandomIndex = FMath::RandRange(0, Assets.Num() - 1);
	FSoftObjectPtr AssetPtr (Manager.GetPrimaryAssetPath(Assets[RandomIndex]));
	if (AssetPtr.IsPending())
	{
		AssetPtr.LoadSynchronous();
	}

	ItemData = Cast<UProject0ItemData>(AssetPtr.Get());
	ensure(ItemData);
}

void AProject0ItemBox::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ItemData == nullptr)
	{
		Destroy();
		return;
	}

	IProject0ItemInterface* OverlappingCharacter = Cast<IProject0ItemInterface>(OtherActor);
	if (OverlappingCharacter)
	{
		OverlappingCharacter->TakeItem(ItemData);
	}

	Effect->ActivateSystem(true);
	SetActorEnableCollision(false);
	Effect->Activate(true);
	Effect->OnSystemFinished.AddDynamic(this, &AProject0ItemBox::OnBoxEffectFinished);
}

void AProject0ItemBox::OnBoxEffectFinished(UParticleSystemComponent* PSystem)
{
	// 변수의 주소를 가지고 있듯이, 함수의 주소를 가지고 호출한다.
	Destroy();
}
