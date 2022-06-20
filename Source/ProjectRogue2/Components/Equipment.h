// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipment.generated.h"

class AItem;
class ABaseCharacter;

UENUM(Blueprintable)
enum class EEquipmentSlot : uint8
{
	Head,
	Chest,
	Legs,
	Feet,
	Hands,
	LeftHand,
	RightHand,
	Count,
};

static constexpr unsigned int kEquipmentSlotCount = static_cast<unsigned int>(EEquipmentSlot::Count);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTROGUE2_API UEquipment : public UActorComponent
{
	GENERATED_BODY()

private:
	ABaseCharacter* Owner;

protected:
	UPROPERTY()
	AItem* EquippedItems[kEquipmentSlotCount];

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TMap<EEquipmentSlot, TSubclassOf<AItem>> StartingItems;

public:	
	// Sets default values for this component's properties
	UEquipment();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void EquipStartingItems();

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	AItem* GetSlot(EEquipmentSlot Slot) { return EquippedItems[static_cast<int>(Slot)]; }

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool TryEquip(EEquipmentSlot Slot, AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool TryUnequip(EEquipmentSlot Slot, bool bIsSwap = false);

	int GetRange() const;
	int GetWeaponDamage() const;
	int GetTotalArmor() const;
};
