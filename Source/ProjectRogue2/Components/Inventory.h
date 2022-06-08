// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "../Item.h"

#include "Inventory.generated.h"

class UInventory;

USTRUCT()
struct FSlot
{
	GENERATED_BODY()

	UInventory* pInventory = nullptr;
	AItem* pClass = nullptr;
	uint32_t Amount = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTROGUE2_API UInventory : public UActorComponent
{
	GENERATED_BODY()

private:
	TArray<FSlot*> Slots;

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void IncreaseInventorySize(const int32_t Amount);
	void DropItem(const int32_t Index);
	bool AddItem(AItem* pClass, int32_t Amount);

	const TArray<FSlot*>& GetSlots() const { return Slots; }
	FSlot* GetSlot(const int32_t Index) const;
	bool IsInventoryFull() const;

private:
	int32_t FillExistingStacks(AItem* pClass, int32_t Amount);
	int32_t FindEmptySlot(bool reverse = false) const;
};
