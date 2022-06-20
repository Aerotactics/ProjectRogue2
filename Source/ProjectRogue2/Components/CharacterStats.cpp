// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStats.h"

// Sets default values for this component's properties
UCharacterStats::UCharacterStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterStats::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCharacterStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterStats::UpdateCoreStats(const int* StartingValues)
{
	for (size_t i = 0; i < CoreStatCount; ++i)
	{
		Stats[(EStats)i] = StartingValues[i];
	}
}

void UCharacterStats::AllocateCoreStatPoint(EStats StatToIncrease)
{
    if ((int)StatToIncrease >= CoreStatCount)
    {
        //Log
        return;
    }

	check(HasStat(StatToIncrease));
    ++Stats[StatToIncrease];
    --StatPointsAvailable;
}

float UCharacterStats::GetStat(EStats Stat) const
{
	if(!HasStat(Stat))
		return 0.0f;
	return Stats[Stat];
}

void UCharacterStats::Increase(EStats Stat, float Amount)
{
	if(!HasStat(Stat))
		return;
    Stats[Stat] += Amount;
}

void UCharacterStats::Decrease(EStats Stat, float Amount)
{
	if (!HasStat(Stat))
		return;
    Stats[Stat] -= Amount;
}