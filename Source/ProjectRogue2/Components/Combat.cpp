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

void UCombat::TakeDamage(int Amount)
{
	//get armor
	//UActorComponent* pComponent = Owner->GetComponentByClass(UEquipment::StaticClass());
	//UEquipment* pEquipment = Cast<UEquipment>(pComponent); 
	int Armor = 0; //pEquipment->GetTotalArmor();

	//goes in UEquipment::GetTotalArmor
	//for (int32 i = 0; i < (int)EEquipmentSlot::Count; ++i)
	//{
	// if (AItem* pItem = EquippedItems[(EEquipmentSlot)i])
	// {
	//  Armor += pItem->GetArmor();
	// }
	//}

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
	int Damage = 0;
	//pComponent = Owner->GetComponentByClass(UEquipment::StaticClass());
	//check(pComponent);
	//UEquipment* pEquipment = Cast<UEquipment>(pComponent);
	//check(pEquipment);
	//AItem* pLeftHand = pEquipment->GetSlot(EEquipmentSlot::LeftHand);
	//AItem* pRightHand = pEquipment->GetSlot(EEquipmentSlot::RightHand);
	pComponent = Owner->GetComponentByClass(UCharacterStats::StaticClass());
	UCharacterStats* pStats = Cast<UCharacterStats>(pComponent);
	//if (pLeftHand)
	//{
	//Damage += pLeftHand->GetDamage() + pStats->GetValue(pLeftHand->GetStatType());
	//}
	//if (pRightHand)
	//{
	//Damage += pRightHand->GetDamage() + pStats->GetValue(pRightHand->GetStatType());
	//
	//} 

	pComponent = Target->GetComponentByClass(UCombat::StaticClass());
	UCombat* pCombat = Cast<UCombat>(pComponent);
	pCombat->TakeDamage(Damage);
}

int UCombat::GetStatModifier(/*AItem* pItem*/)
{
	//EStats StatType = pItem->GetStatType();
	//return pStats->GetValue(EStats::Strength);
	//if(StatType == EStats::Strength)
	//{
	//}
	//else if (StatType == EStats::Dexterity)
	//{
	//return pStats->GetValue(EStats::Dexterity)
	//}
}