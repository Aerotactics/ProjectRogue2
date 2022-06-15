// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"
#include "../Item.h"
#include "Inventory/Inventory.h"
#include "../Characters/BaseCharacter.h"
#include "../Components/CharacterClass.h"

// Sets default values for this component's properties
UEquipment::UEquipment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEquipment::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Owner = Cast<ABaseCharacter>(GetOwner());
}

bool UEquipment::TryEquip(EEquipmentSlot Slot, AItem* Item)
{
	//weapons are typically equipped in the right hand
	//so, if we are equipping in the right hand
	if (Slot == EEquipmentSlot::RightHand)
	{
		AItem* CurrentlyEquipped = GetSlot(Slot);
		//but we already have something in that hand
		if (CurrentlyEquipped)
		{
			//put it in the other hand
			EquippedItems[static_cast<int>(EEquipmentSlot::LeftHand)] = Item;
			Item->OnEquip(Cast<ABaseCharacter>(Owner));
			return true;
		}
	}

	if (Slot != Item->GetEquipSlot())
	{
		//Log
		return false;
	}

	// Level Requirement
	int32 LevelRequirement = Item->GetLevelRequirement();
	if (LevelRequirement > 0)
	{
		UCharacterClass* ClassComponent = Owner->GetComponent<UCharacterClass>();
		if (ClassComponent != nullptr && ClassComponent->GetLevel() < LevelRequirement)
		{
			// Log
			return false;
		}
	}

	// Stat Level Requirement
	int32 StatLevelRequirement = Item->GetStatLevelRequirement();
	if (StatLevelRequirement > 0)
	{
		UCharacterStats* StatsComponent = Owner->GetComponent<UCharacterStats>();
		if (StatsComponent != nullptr && StatsComponent->GetStat(Item->GetStatType()) < StatLevelRequirement)
		{
			// Log
			return false;
		}
	}

	if (!TryUnequip(Slot, true))
	{
		//Log
		return false;
	}

	EquippedItems[(int)Slot] = Item;
	Item->OnEquip(Cast<ABaseCharacter>(Owner));
	return true;
}

bool UEquipment::TryUnequip(EEquipmentSlot Slot, bool bIsSwap)
{
	// Check if slot is open
	AItem* CurrentlyEquipped = GetSlot(Slot);
	if (!CurrentlyEquipped)
	{
		//if there is nothing equipped, its "successful"
		return true;
	}

	CurrentlyEquipped->OnUnequip(Cast<ABaseCharacter>(GetOwner()));
	UActorComponent* pComponent = Owner->GetComponentByClass(UInventory::StaticClass());
	UInventory* pInventory = Cast<UInventory>(pComponent);

	//if we are swapping an equipped weapon with a weapon in the inventory, the inventory can be full
	if (pInventory->IsInventoryFull() && !bIsSwap)
	{
		return false;
	}

	// Try Add the item to inventory
	pInventory->AddItem(CurrentlyEquipped->GetClass(), 1);
	//destroy the item actor
	EquippedItems[static_cast<size_t>(Slot)]->Destroy();
	//remove item from equipped items
	EquippedItems[static_cast<size_t>(Slot)] = nullptr;
	return true;
}

int UEquipment::GetRange() const
{
	AItem* pLeftHand = EquippedItems[static_cast<int>(EEquipmentSlot::LeftHand)];
	AItem* pRightHand = EquippedItems[static_cast<int>(EEquipmentSlot::LeftHand)];

	int Range = 0;
	if (pLeftHand)
	{
		pLeftHand->GetRange();
	}
	if (pRightHand)
	{
		if (int RightRange = pRightHand->GetRange() > Range)
		{
			Range = RightRange;
		}
	}

	return Range;
}

int UEquipment::GetWeaponDamage() const
{
	int Damage = 0;
	AItem* pLeftHand = EquippedItems[static_cast<int>(EEquipmentSlot::LeftHand)];
	AItem* pRightHand = EquippedItems[static_cast<int>(EEquipmentSlot::RightHand)];
	if (pLeftHand)
	{
		Damage += pLeftHand->GetDamage();
	}
	if (pRightHand)
	{
		Damage += pRightHand->GetDamage();
	}

	return Damage;
}

int UEquipment::GetTotalArmor() const
{
	int Armor = 0;
	for (const auto& pItem : EquippedItems)
	{
		if (pItem)
		{
			Armor = pItem->GetArmor();
		}
	}
	return Armor;
}