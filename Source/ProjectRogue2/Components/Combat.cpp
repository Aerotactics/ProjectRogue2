// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat.h"

// Sets default values for this component's properties
UCombat::UCombat()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombat::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCombat::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombat::TakeDamage(int Amount)
{
	CurrentHealth -= Amount;
	if (CurrentHealth < 0)
	{
		CurrentHealth = 0;
	}
}

void UCombat::Heal(int Amount)
{
	CurrentHealth += Amount;
	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}