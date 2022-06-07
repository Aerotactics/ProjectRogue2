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

void UCharacterStats::UpdateStats(const int* StartingValues, const int Min, const int Max)
{
	for (size_t i = 0; i < StatCount; ++i)
	{
		Stats[i].Value = StartingValues[i];
		Stats[i].Min = Min;
		Stats[i].Max = Max;
	}
}

void UCharacterStats::AllocatePoint(EStats StatToIncrease)
{
    Stat& stat = Stats[static_cast<size_t>(StatToIncrease)];
    ++stat.Value;
    if (stat.Value > stat.Max)
    {
        stat.Value = stat.Max;
    }
}

void UCharacterStats::Increase(EStats StatToIncrease, const int Amount)
{
    Stat& stat = Stats[static_cast<size_t>(StatToIncrease)];
    if (stat.Max > 0)
    {
        stat.Value += Amount;
    }
    if (stat.Value > stat.Max)
    {
        stat.Value = stat.Max;
    }
}

void UCharacterStats::Decrease(EStats StatToIncrease, const int Amount)
{
    Stat& stat = Stats[static_cast<size_t>(StatToIncrease)];
    if (stat.Value > stat.Min)
    {
        stat.Value -= Amount;
    }
    if (stat.Value < stat.Min)
    {
        stat.Value = stat.Min;
    }
}