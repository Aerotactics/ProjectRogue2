// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStats.generated.h"

UENUM()
enum class EStats : uint8
{
    // CORE STATS (Available to player)
    Strength,
    Dexterity,
    Intelligence,
    Vitality,
    Luck,

    // RESOURCES, SKILLS, MISC (Transparent to player)
    CurrentHealth,
    MaxHealth,
    CurrentMana,
    MaxMana,
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

    Count
};
static constexpr size_t CoreStatCount = 5;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTROGUE2_API UCharacterStats : public UActorComponent
{
	GENERATED_BODY()

private:
    float Stats[(int)EStats::Count];
    int StatPointsAvailable;

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
    void AddCoreStatPoints(const int Amount) { StatPointsAvailable += Amount; }
    void AllocateCoreStatPoint(EStats StatToIncrease);

    void Increase(EStats StatToIncrease, float Amount = 1);
    void Decrease(EStats StatToIncrease, float Amount = 1);

    int GetAvailableStatPoints() const { return StatPointsAvailable; }
    float GetStat(EStats stat) const { return Stats[static_cast<size_t>(stat)]; }
};