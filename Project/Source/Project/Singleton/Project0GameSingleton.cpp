// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/Project0GameSingleton.h"
#include "GameData/Project0CharacterStat.h"

UProject0GameSingleton::UProject0GameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/GameData/DT_Project0CharacterStat.DT_Project0CharacterStat'"));

	if (DataTableRef.Succeeded())
	{
		const UDataTable* DataTable = DataTableRef.Object;

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, CharacterStatTable, [](uint8* Value)
			{
				return *reinterpret_cast<FProject0CharacterStat*>(Value);
			});
	}

	CharacterMaxLevel = CharacterStatTable.Num();
}

UProject0GameSingleton* UProject0GameSingleton::GetInstance()
{
	UProject0GameSingleton* Singleton = CastChecked<UProject0GameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return Singleton;
	}

	// Singleton이 없으면 새로 생성 (다만 이 단계까지는 권장하지 않기 때문에 주의한다.)
	return NewObject<UProject0GameSingleton>();
}

FProject0CharacterStat UProject0GameSingleton::GetCharacterStat(int32 InLevel) const
{
	if (CharacterStatTable.IsValidIndex(InLevel - 1))
	{
		return CharacterStatTable[InLevel];
	}
	else
	{
		return FProject0CharacterStat();
	}
}