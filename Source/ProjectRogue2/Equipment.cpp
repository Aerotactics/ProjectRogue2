// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"
#include "Item.h"

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
	
}


// Called every frame
void UEquipment::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UEquipment::TryEquip(EEquipmentSlot Slot, AItem* Item)
{
	if (Slot != Item->GetEquipSlot())
	{
		//Log
		return false;
	}

	AActor* Owner = GetOwner();
	UActorComponent* Component = Owner->GetComponentByClass(UEquipment::StaticClass());
	UEquipment* Equipment = Cast<UEquipment>(Component);

	if (!TryUnequip(Slot))
	{
		//Log
		return false;
	}

	// Remove this from inventory
	EquippedItems[(int)Slot] = Item;
	Item->OnEquip(Cast<ABaseCharacter>(Owner));
	return true;
}

bool UEquipment::TryUnequip(EEquipmentSlot Slot)
{
	// Check if slot is open
	AItem* CurrentlyEquipped = GetSlot(Slot);
	if (CurrentlyEquipped != nullptr)
	{
		// Try Add the item to inventory
		CurrentlyEquipped->OnUnequip(Cast<ABaseCharacter>(GetOwner()));
	}
	return true;
}

