// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

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
	
}

void UInventory::IncreaseInventorySize(const int32_t Amount)
{
    Slots.Reserve(Slots.Num() + Amount);
}

bool UInventory::AddItem(AItem* pClass, int32_t Amount)
{
    if (pClass->GetMaxStackSize() > 1)
    {
        //fill any existing stacks and update amount with how much remains
        Amount = FillExistingStacks(pClass, Amount);
    }

    if (IsInventoryFull())
    {
        //LOG inventory is full
        return false;
    }

    int32_t emptySlot = FindEmptySlot();
    if (emptySlot == -1)
    {
        //LOG inventory is full
        return false;
    }

    //LOG
    Slots[emptySlot]->pClass = pClass;
    //LOG
    Slots[emptySlot]->Amount = Amount;
    return true;
}

void UInventory::DropItem(const int32_t Index)
{
    if (Index < 0 || Index >= Slots.Num())
    {
        //LOG
        return;
    }

    FSlot* pSlot = Slots[Index];
    //create item actor
    pSlot->pClass = nullptr;
    pSlot->Amount = 0;
}

FSlot* UInventory::GetSlot(const int32_t Index) const
{
    check(Index >= 0 && Index < Slots.Num());
    return Slots[Index];
}

bool UInventory::IsInventoryFull() const
{
    for (const auto& pSlot : Slots)
    {
        //if any pSlot has an invalid class, that pSlot is empty
        if (!pSlot->pClass)
        {
            //so the inventory is not full
            return false;
        }
    }
    return true;
}


int32_t UInventory::FillExistingStacks(AItem* pClass, int32_t Amount)
{
    for (size_t i = 0; i < Slots.Num(); ++i)
    {
        FSlot* pSlot = Slots[i];
        if (pClass == pSlot->pClass)
        {
            uint32_t newStackCount = pSlot->Amount + Amount;
            uint32_t maxStackSize = pClass->GetMaxStackSize();
            //if the amount being added exceeds a stack
            if (newStackCount > maxStackSize)
            {
                //add the difference and subtract that difference from amount being added
                uint32_t difference = newStackCount - maxStackSize;
                Amount -= difference;
                pSlot->Amount += difference;
            }
            //if the amount being added doesnt exceed a stack
            else
            {
                pSlot->Amount += Amount;
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
            if (Slots[i]->pClass == nullptr)
            {
                return i;
            }
        }
    }
    else
    {
        for (int i = 0; i < Slots.Num(); ++i)
        {
            if (Slots[i]->pClass == nullptr)
            {
                return i;
            }
        }
    }

    return -1;
}
