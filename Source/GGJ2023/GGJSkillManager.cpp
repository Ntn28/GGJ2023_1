// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJSkillManager.h"



// Sets default values
AGGJSkillManager::AGGJSkillManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGGJSkillManager::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(GameplayStruct))
	{
		NumOfSkills = GameplayStruct->MaxSkillToDisplay;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameplayStructNull"));
	}
	//SkillSelector();

	//FPlayerInfo Info;
	//Info.bHasOneTime = false;
	//Info.CurrentHp = 120;
	//Info.CurrentAttackSpeed = 0.5f;
	//Info.CurrentInvincibility = 1;
	//Info.CurrentMaxHP = 200;
	//Info.CurrentMovementSpeed = 12;

	//SkillSelector(Info);
}




void AGGJSkillManager::SkillSelector(FPlayerInfo& Data)
{
	FPlayerStats Stats = GameplayStruct->Player;
	TMap<EStats, FSkillDataStruct>SkillDataMapBuff;
	TMap<EStats, FSkillDataStruct>SkillDataMapDeBuff;
	TArray<FSkillDataStruct*> SkillList;
	GameplayStruct->SkillData->GetAllRows(FString(""), SkillList);

	for(FSkillDataStruct* SingleSkill : SkillList)
	{
		SkillDataMapBuff.Add(SingleSkill->StatsToModify, *SingleSkill);
		if (SingleSkill->SkillType != ECategory::EOneTime)
		{
			SkillDataMapDeBuff.Add(SingleSkill->StatsToModify, *SingleSkill);
		}
	}

	CheckConstrain(Data.CurrentMaxHP, Stats.MinHp, Data.CurrentHp, EStats::EHp, SkillDataMapBuff, SkillDataMapDeBuff);
	CheckConstrain(Stats.MaxMoveSpeed, Stats.MinMoveSpeed, Data.CurrentMovementSpeed, EStats::EMovementSpeed, SkillDataMapBuff, SkillDataMapDeBuff);
	CheckConstrain(Stats.MaxAttackSpeed, Stats.MinAttackSpeed, Data.CurrentAttackSpeed, EStats::EAttackSpeed, SkillDataMapBuff, SkillDataMapDeBuff);
	CheckConstrain(Stats.MaxInvincibility, Stats.MinInvincibility, Data.CurrentInvincibility, EStats::EAttackSpeed, SkillDataMapBuff, SkillDataMapDeBuff);
	
	if (SkillDataMapBuff.Num() >= 3)
	{
		while (true)
		{
			if (BuffList.Num() == 3)
			{
				break;
			}
			EStats SkillToPick = (EStats)(FMath::RandRange(0, EStats::ENone));
			if (SkillDataMapBuff.Contains(SkillToPick))
			{
				FSkillStruct Buff;
				FillStruct(Buff, SkillDataMapBuff[SkillToPick], true);
				BuffList.Add(Buff);
				SkillDataMapBuff.Remove(SkillToPick);
			}

		}
	}
	if (SkillDataMapDeBuff.Num() >= 3)
	{
		while (true)
		{
			if (DebuffList.Num() == 3)
			{
				break;
			}
			EStats SkillToPick = (EStats)(FMath::RandRange(0, EStats::ENone));
			if (SkillDataMapDeBuff.Contains(SkillToPick))
			{
				FSkillStruct Debuff;
				FillStruct(Debuff, SkillDataMapDeBuff[SkillToPick], false);
				DebuffList.Add(Debuff);
				SkillDataMapDeBuff.Remove(SkillToPick);
			}

		}
	}
}

void AGGJSkillManager::CheckConstrain(const float& MAXValue, const float& MINValue,const float& CurrentValue,EStats Stat,TMap<EStats, FSkillDataStruct>& BuffMap, TMap<EStats, FSkillDataStruct>& DebuffMap)
{
	if (CurrentValue >= MAXValue)
	{
		BuffMap.Remove(Stat);
	}
	if (CurrentValue <= MINValue)
	{
		DebuffMap.Remove(Stat);
	}
}

void AGGJSkillManager::FillStruct(FSkillStruct& Struct,const FSkillDataStruct& Skill,bool bIsBuff)
{
	Struct.bIsBuff = bIsBuff;
	Struct.Icon = Skill.Icon;
	Struct.SkillName = Skill.SkillName;
	Struct.SkillType = Skill.SkillType;
	Struct.StatsToModify = Skill.StatsToModify;
	Struct.Value = Skill.BuffValue ? bIsBuff : Skill.DebuffValue;
}

// Called every frame
void AGGJSkillManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


TArray<FSkillStruct> AGGJSkillManager::GetBuffs(FPlayerInfo Data, TArray<FSkillStruct>& Debuffs)
{
	BuffList.Empty();
	DebuffList.Empty();

	SkillSelector(Data);
	Debuffs = DebuffList;

	return BuffList;
}

TArray<FSkillStruct> AGGJSkillManager::GetDebuffs()
{
	return TArray<FSkillStruct>();
}

