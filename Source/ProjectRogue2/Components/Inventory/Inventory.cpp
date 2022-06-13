// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "../../Characters/BaseCharacter.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
    Owner = Cast<ABaseCharacter>(GetOwner());
}

bool UInventory::DecreaseGold(const int32 Amount)
{
    if ((Gold - Amount) < 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot remove %d gold, only have %d"), Amount, Gold);
        return false;
    }

    Gold -= Amount;
    if (Gold < 0)
    {
        Gold = 0;
    }

    return true;
}

void UInventory::IncreaseInventorySize(const int32 Amount)
{
    int32 i = Slots.Num();
    Slots.Reserve(Slots.Num() + Amount);
    for (; i < Amount; ++i)
    {
        FInventorySlot Slot;
        Slot.Index = i;
        Slots.Emplace();
    }
}

bool UInventory::AddItem(TSubclassOf<AItem> pClass, int32 Amount)
{
    auto Defaults = pClass->GetDefaultObject();
    AItem* Item = Cast<AItem>(Defaults);
    if (Item->GetMaxStackSize() > 1)
    {
        //fill any existing stacks and update amount with how much remains
        Amount = FillExistingStacks(pClass, Amount);
    }

    if (IsInventoryFull())
    {
        //LOG inventory is full
        return false;
    }

    int32 emptySlot = FindEmptySlot();
    if (emptySlot == -1)
    {
        //LOG inventory is full
        return false;
    }

    //LOG
    Slots[emptySlot].Class = pClass;
    //LOG
    Slots[emptySlot].Amount = Amount;
    return true;
}

bool UInventory::UseItem(const int32 Index, int32 Amount)
{
    if (Index < 0 || Index >= Slots.Num())
    {
        //LOG
        return false;
    }

    auto& Slot = Slots[Index];
    if (!Slot.Class)
    {
        //LOG
        return false;
    }

    //make sure we dont attempt to use more than there is in the slot
    if (Amount > Slot.Amount)
    {
        Amount = Slot.Amount;
    }

    AItem* Item = GetWorld()->SpawnActor<AItem>(Slot.Class);
    for (int32 i = 0; i < Amount; ++i)
    {
        Item->OnUse(Owner);
        --Slot.Amount;
    }

    if (Slot.Amount == 0)
    {
        Slot.Class = nullptr;
    }

    return true;
}

int32 UInventory::FindItemByClass(TSubclassOf<AItem> Class, bool Reverse) const
{
    if (Reverse)
    {
        for (int i = Slots.Num() - 1; i >= 0; --i)
        {
            if (Slots[i].Class == Class)
            {
                return i;
            }
        }
    }
    else
    {
        for (int i = 0; i < Slots.Num(); ++i)
        {
            if (Slots[i].Class == Class)
            {
                return i;
            }
        }
    }

    return -1;
}

void UInventory::DropItem(const int32 Index, const int32 Amount)
{
    //create loot actor
    DeleteItem(Index, Amount);
}

void UInventory::DropStack(const int32 Index)
{
    auto& Slot = GetSlot(Index);
    DropItem(Index, Slot.Amount);
}

void UInventory::DeleteItem(const int32 Index, const int32 Amount)
{
    if (Index < 0 || Index >= Slots.Num())
    {
        //LOG
        return;
    }

    FInventorySlot& pSlot = Slots[Index];
    //remove item from inventory without creating loot actor, deleting the item from the game
    pSlot.Amount -= Amount;
    if (pSlot.Amount <= 0)
    {
        pSlot.Class = nullptr;
        pSlot.Amount = 0;
    }
}

void UInventory::RemoveItemByClass(TSubclassOf<AItem> Class, int32 Amount, bool Reverse)
{
    while (Amount > 0)
    {
        const int32 Index = FindItemByClass(Class, Reverse);
        if (Index == -1)
        {
            //LOG
            return;
        }

        //amount = 300, slot = 36/50, LeftOvers = -264
        //amount = 5,   slot = 36/50, LeftOvers = 31
        //amount = 14,  slot = 36/50, LeftOvers = 22

        FInventorySlot& Slot = Slots[Index];
        const int32 LeftOvers = Slot.Amount - Amount;
        Amount -= Slot.Amount;
        if (LeftOvers > 0)
        {
            DropItem(Index, Amount);
        }
        else
        {
            DropStack(Index);
        }
    }
}

const FInventorySlot& UInventory::GetSlot(const int32 Index) const
{
    check(Index >= 0 && Index < Slots.Num());
    //LOG?
    return Slots[Index];
}

bool UInventory::IsInventoryFull() const
{
    for (const auto& pSlot : Slots)
    {
        //if any pSlot has an invalid class, that pSlot is empty
        if (!pSlot.Class)
        {
            //so the inventory is not full
            return false;
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////

int32_t UInventory::FillExistingStacks(TSubclassOf<AItem> pClass, int32 Amount)
{
    auto Defaults = pClass->GetDefaultObject();
    AItem* Item = Cast<AItem>(Defaults);
    for (size_t i = 0; i < Slots.Num(); ++i)
    {
        FInventorySlot& pSlot = Slots[i];
        if (pClass == pSlot.Class)
        {
            uint32_t newStackCount = pSlot.Amount + Amount;
            uint32_t maxStackSize = Item->GetMaxStackSize();
            //if the amount being added exceeds a stack
            if (newStackCount > maxStackSize)
            {
                //add the difference and subtract that difference from amount being added
                uint32_t difference = newStackCount - maxStackSize;
                Amount -= difference;
                pSlot.Amount += difference;
            }
            //if the amount being added doesnt exceed a stack
            else
            {
                pSlot.Amount += Amount;
                Amount = 0;
                //we have nothing left to add, so break
                break;
            }
        }
    }
    return Amount;
}

int UInventory::FindEmptySlot(bool reverse) const
{
    if (reverse)
    {
        for (int i = Slots.Num() - 1; i >= 0; --i)
        {
            if (Slots[i].Class == nullptr)
            {
                return i;
            }
        }
    }
    else
    {
        for (int i = 0; i < Slots.Num(); ++i)
        {
            if (Slots[i].Class == nullptr)
            {
                return i;
            }
        }
    }

    return -1;
}
