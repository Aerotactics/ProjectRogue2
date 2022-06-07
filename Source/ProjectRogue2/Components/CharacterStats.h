// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStats.generated.h"

UENUM()
enum class EStats : uint8
{
    Strength,
    Dexterity,
    Intelligence,
    Vitality,
    Luck,
    Health,
    Mana,
};
static constexpr size_t StatCount = static_cast<size_t>(EStats::Luck) + 1;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTROGUE2_API UCharacterStats : public UActorComponent
{
	GENERATED_BODY()

public:
    struct Stat
    {
        FString m_name;
        int Value;
        int Min;
        int Max;
    };

private:
    Stat Stats[StatCount];
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

    void UpdateStats(const int* StartingValues, const int Min, const int Max);
    void AddStatPoints(const int Amount) { StatPointsAvailable += Amount; }
    void AllocatePoint(EStats StatToIncrease);

    void Increase(EStats StatToIncrease, const int Amount = 1);
    void Decrease(EStats StatToIncrease, const int Amount = 1);
    void IncreaseMin(EStats stat, const int Amount = 1) { Stats[static_cast<size_t>(stat)].Min += Amount; }
    void IncreaseMax(EStats stat, const int Amount = 1) { Stats[static_cast<size_t>(stat)].Max += Amount; }
    void DecreaseMin(EStats stat, const int Amount = 1) { Stats[static_cast<size_t>(stat)].Min -= Amount; }
    void DecreaseMax(EStats stat, const int Amount = 1) { Stats[static_cast<size_t>(stat)].Max -= Amount; }

    const Stat& GetStat(EStats stat) const { return Stats[static_cast<size_t>(stat)]; }
    int GetAvailableStatPoints() const { return StatPointsAvailable; }

    int GetValue(EStats stat) const { return Stats[static_cast<size_t>(stat)].Value; }
    int GetMin(EStats stat) const { return Stats[static_cast<size_t>(stat)].Min; }
    int GetMax(EStats stat) const { return Stats[static_cast<size_t>(stat)].Max; }

};
using Stat = UCharacterStats::Stat;