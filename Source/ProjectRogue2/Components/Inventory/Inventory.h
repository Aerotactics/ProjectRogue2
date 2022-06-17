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
	ABaseCharacter* Owner;
	TArray<FInventorySlot> Slots;
	int32 Gold;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 StartingSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 StartingGold;

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void IncreaseGold(const int32 Amount) { Gold += Amount; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool DecreaseGold(const int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetGold() const { return Gold; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void IncreaseInventorySize(const int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DropItem(const int32 Index, const int32 Amount = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DropStack(const int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DeleteItem(const int32 Index, const int32 Amount = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(TSubclassOf<AItem> Class, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool UseItem(const int32 Index, int32 Amount = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 FindItemByClass(TSubclassOf<AItem> Class, bool Reverse = true) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItemByClass(TSubclassOf<AItem> Class, int32 Amount, bool Reverse = true);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	const TArray<FInventorySlot>& GetSlots() const { return Slots; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	const FInventorySlot& GetSlot(const int32 Index) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsInventoryFull() const;

private:
	int32 FillExistingStacks(TSubclassOf<AItem> Class, int32 Amount);
	int32 FindEmptySlot(bool reverse = false) const;
	void ShiftEmptySlots();
};
