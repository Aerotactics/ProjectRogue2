// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"
#include "../Item.h"
#include "Inventory.h"
#include "../Characters/BaseCharacter.h"

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
	if (Slot != Item->GetEquipSlot())
	{
		//Log
		return false;
	}

	UActorComponent* Component = Owner->GetComponentByClass(UEquipment::StaticClass());
	UEquipment* Equipment = Cast<UEquipment>(Component);

	if (!TryUnequip(Slot, true))
	{
		//Log
		return false;
	}

	// Remove this from inventory
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

	//if we are swapping an equipped weapon with a weapon in the inventory
	if (bIsSwap)
	{
		//add item to inventory
		pInventory->AddItem(CurrentlyEquipped, 1);
		//remove item from equipped items
		EquippedItems[static_cast<size_t>(Slot)] = nullptr;
	}

	if (pInventory->IsInventoryFull())
	{
		return false;
	}

	// Try Add the item to inventory
	pInventory->AddItem(CurrentlyEquipped, 1);
	return true;
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