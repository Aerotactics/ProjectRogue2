// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterClass.h"
#include "CharacterStats.h"

// Sets default values for this component's properties
UCharacterClass::UCharacterClass()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Level = 0;
	Experience = 0;
	RequiredExperience = 0;
	RequiredExperienceMultiplier = 1.5f;
	StatPointsPerLevel = 5;
	// ...
}


// Called when the game starts
void UCharacterClass::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCharacterClass::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterClass::GainExperience(const int Amount)
{
	Experience += Amount;
	if (Experience >= RequiredExperience)
	{
		RequiredExperience += (RequiredExperience * RequiredExperienceMultiplier);
		++Level;

		UActorComponent* pComponent = GetOwner()->GetComponentByClass(UCharacterStats::StaticClass());
		check(pComponent);
		UCharacterStats* pStat = Cast<UCharacterStats>(pComponent);
		if (pStat)
		{
			pStat->AddStatPoints(StatPointsPerLevel);
		}
	}
}
