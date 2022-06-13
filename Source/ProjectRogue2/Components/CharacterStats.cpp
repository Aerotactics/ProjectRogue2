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
		Stats[i] = StartingValues[i];
	}
}

void UCharacterStats::AllocateCoreStatPoint(EStats StatToIncrease)
{
    if ((int)StatToIncrease >= CoreStatCount)
    {
        //Log
        return;
    }

    ++Stats[static_cast<size_t>(StatToIncrease)];
    --StatPointsAvailable;
}

void UCharacterStats::Increase(EStats StatToIncrease, float Amount)
{
    Stats[static_cast<size_t>(StatToIncrease)] += Amount;
}

void UCharacterStats::Decrease(EStats StatToIncrease, float Amount)
{
    Stats[static_cast<size_t>(StatToIncrease)] -= Amount;
}