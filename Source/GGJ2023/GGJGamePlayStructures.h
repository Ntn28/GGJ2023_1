// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "GGJGamePlayStructures.generated.h"

UENUM(BlueprintType)
enum ECategory
{
	EDefense	UMETA(DisplayName = "Defense"),
	EAttack		UMETA(DisplayName = "Attack"),
	EInstant	UMETA(DisplayName = "Instant"),
	EOneTime	UMETA(DisplayName = "OneTime"),
	ELast		UMETA(DisplayName = "Last")
};

UENUM(BlueprintType)
enum EStats
{
	EHp					UMETA(DisplayName = "HP"),
	EMovementSpeed		UMETA(DisplayName = "MovementSpeed"),
	EJumpHeight			UMETA(DisplayName = "JumpHeight"),
	EDashInvincibility	UMETA(DisplayName = "DashInvincibility"),
	EAttackDamage		UMETA(DisplayName = "AttackDamage"),
	EAttackSpeed		UMETA(DisplayName = "AttackSpeed"),
	EProjectileAmount		UMETA(DisplayName = "ProjectileAmount"),
	EProjectileSpeed		UMETA(DisplayName = "ProjectileSpeed"),
	EAOEAreaRadius			UMETA(DisplayName = "AOESize"),
	EOneTimes			UMETA(DisplayName = "OneTimes"),
	EHealTree			UMETA(DisplayName = "HealTree"),
	EHealPlayer			UMETA(DisplayName = "HealPlayer"),
	ENone				UMETA(DisplayName = "None"),

};

USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float CurrentMaxHP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float CurrentHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		bool bHasOneTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float CurrentMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float CurrentAttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float CurrentInvincibility;
};

USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MinHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float StartingHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MaxJumpHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MinJumpHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float StartingJumpHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MaxMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MinMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MaxAttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MinAttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tree)
		float MaxTreeHp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tree)
		float MinTreeHp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float MaxInvincibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float MinInvincibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float StartingInvincibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MinAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float StartingAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MinProjectile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MaxProjectile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float StartingProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MinProjectileSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float StartingProjectileSpeed;
};

USTRUCT(BlueprintType)
struct FSkillDataStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FSkillDataStruct(){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	FName SkillName = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	TEnumAsByte<ECategory> SkillType = ECategory::ELast;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	TEnumAsByte<EStats> StatsToModify = EStats::ENone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	float DebuffValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	float BuffValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	UTexture2D* Icon = nullptr;

};

USTRUCT(BlueprintType)
struct FSkillStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
		FName SkillName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
		TEnumAsByte<ECategory> SkillType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
		TEnumAsByte<EStats> StatsToModify;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
		float Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
		bool bIsBuff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
		UTexture2D* Icon = nullptr;
};
/**
 * 
 */
UCLASS()
class GGJ2023_API UGGJGamePlayStructures : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		UDataTable* SkillData = nullptr;

	UPROPERTY(EditAnywhere)
		int MaxSkillToDisplay = 6;

	UPROPERTY(EditAnywhere)
		FPlayerStats Player;
};
