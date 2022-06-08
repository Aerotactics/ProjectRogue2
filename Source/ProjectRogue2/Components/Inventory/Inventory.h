// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "../../Item.h"
#include "InventorySlot.h"

#include "Inventory.generated.h"

class UInventory;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTROGUE2_API UInventory : public UActorComponent
{
	GENERATED_BODY()

private:
	TArray<FInventorySlot> Slots;

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void IncreaseInventorySize(const int32 Amount);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DropItem(const int32 Index);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(TSubclassOf<AItem> Class, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	const TArray<FInventorySlot>& GetSlots() const { return Slots; }
	const FInventorySlot& GetSlot(const int32 Index) const;
	bool IsInventoryFull() const;

private:
	int32 FillExistingStacks(TSubclassOf<AItem> Class, int32 Amount);
	int32 FindEmptySlot(bool reverse = false) const;
};
