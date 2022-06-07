// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat.h"
#include "CharacterStats.h"
#include "../Characters/BaseCharacter.h"

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
	Owner = Cast<ABaseCharacter>(GetOwner());
}


// Called every frame
void UCombat::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombat::TakeDamage(int Amount)
{
	//get armor
	//UActorComponent* pComponent = Owner->GetComponentByClass(UEquipment::StaticClass());
	//UEquipment* pEquipment = Cast<UEquipment>(pComponent); 
	int Armor = 0; //pEquipment->GetTotalArmor();

	CurrentHealth -= (Amount - Armor);
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

void UCombat::Attack(ABaseCharacter* Target)
{
	UActorComponent* pComponent = nullptr;
	//get weapon
	//pComponent = Owner->GetComponentByClass(UEquipment::StaticClass());
	//get strength
	pComponent = Owner->GetComponentByClass(UCharacterStats::StaticClass());
	UCharacterStats* pStats = Cast<UCharacterStats>(pComponent);
	int Damage = 0;
	//if weapon.stat == Strength
	{
		Damage += pStats->GetValue(EStats::Strength);
	}
	//else if weapon.stat == Dexterity
	{
		//Damage += pStats->GetValue(EStats::Dexterity);
	}

	pComponent = Target->GetComponentByClass(UCombat::StaticClass());
	UCombat* pCombat = Cast<UCombat>(pComponent);
	pCombat->TakeDamage(Damage);
}