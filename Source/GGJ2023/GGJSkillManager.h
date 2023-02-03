// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGJGamePlayStructures.h"
#include "GGJSkillManager.generated.h"


UCLASS()
class GGJ2023_API AGGJSkillManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGGJSkillManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
	int NumOfSkills;
private:
	UFUNCTION()
	void SkillSelector(FPlayerInfo& Data);
	//void SelectSingleSkill(EConstrain Constrain);
	UFUNCTION()
	void FillStruct(FSkillStruct& Struct, const FSkillDataStruct& Skill,bool bIsBuff);
	UPROPERTY()
	TArray<FSkillStruct> BuffList = {};
	UPROPERTY()
	TArray<FSkillStruct> DebuffList = {};

	void CheckConstrain(const float& MAXValue, const float& MINValue, const float& CurrentValue, EStats Stat, TMap<EStats, FSkillDataStruct>& BuffMap, TMap<EStats, FSkillDataStruct>& DebuffMap);


	//EConstrain CurrentConstrain;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Return Array of skills buff"))
	TArray<FSkillStruct> GetBuffs(FPlayerInfo Data, TArray<FSkillStruct>& Debuffs);

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Return Array of skills buff"))
	TArray<FSkillStruct> GetDebuffs();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip = "Collection of datas"))
	UGGJGamePlayStructures* GameplayStruct = nullptr;

};
