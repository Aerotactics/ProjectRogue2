// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InventorySlot.generated.h"

class UInventory;
class AItem;

USTRUCT(Blueprintable)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	UInventory* Inventory = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<AItem> Class = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	int32 Amount = 0;
};
