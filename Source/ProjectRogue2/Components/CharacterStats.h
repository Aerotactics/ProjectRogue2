// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStats.generated.h"

//enemy party and leader

UENUM()
enum class EClass
{
    Warrior,
    Rogue,
    Paladin,
    Cleric,
    Mage,
    Warlock,
    Hunter,
};

UENUM(Blueprintable)
enum class EStats : uint8
{
    // CORE STATS (Available to player)
    Strength,
    Dexterity,
    Intelligence,
    Vitality,
    Luck,

    StatPointsPerLevel,
    StatPointsAvailable,

    // RESOURCES, SKILLS, MISC (Transparent to player)
    CurrentHealth,
    MaxHealth,
    CurrentMana,
    MaxMana,
    Level,
    Experience,
    RequiredExperience,
    RequiredExperienceMultiplier,
    CarryCapacity,

    // BACKGROUND (Mostly hidden to player)
    HitChancePercent,
    DodgeChancePercent,
    MeleeDamagePercent,
    RangeDamagePercent,
    HealthRegenerationPercent,
    ManaRegenerationPercent,
    SpellEffectPercent,
    DamageResistPercent,
    MagicResistPercent,
    PoisonResistPercent,
    GoldFindPercent,
    MagicFindPercent,
    ExperienceGainPercent,

    Count
};
static constexpr size_t CoreStatCount = 5;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTROGUE2_API UCharacterStats : public UActorComponent
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    EClass CharacterClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    TMap<EStats, float> Stats;

public:	
	// Sets default values for this component's properties
	UCharacterStats();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // TODO: Revisit this during character creation
    void UpdateCoreStats(const int* StartingValues);
    void AddAvailableStatPoints(const int Amount) { Increase(EStats::StatPointsAvailable, Amount); }
    void AllocateCoreStatPoint(EStats StatToIncrease);

    bool HasStat(EStats Stat) const { return Stats.Contains(Stat); }
    float GetStat(EStats Stat) const;
    void SetStat(EStats Stat, float Value) { Stats[Stat] = Value; }
    
    void Increase(EStats StatToIncrease, float Amount = 1);
    void Decrease(EStats StatToIncrease, float Amount = 1);

};