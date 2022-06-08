// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipment.generated.h"

class AItem;
class ABaseCharacter;

UENUM()
enum class EEquipmentSlot : uint8
{
	None,
	Head,
	Chest,
	Legs,
	Feet,
	Hands,
	LeftHand,
	RightHand,
	
	Count,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTROGUE2_API UEquipment : public UActorComponent
{
	GENERATED_BODY()

private:
	ABaseCharacter* Owner;

protected:
	UPROPERTY()
	AItem* EquippedItems[(int)EEquipmentSlot::Count];

public:	
	// Sets default values for this component's properties
	UEquipment();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	AItem* GetSlot(EEquipmentSlot Slot) { return EquippedItems[(int)Slot]; }

	UFUNCTION(BlueprintCallable)
	bool TryEquip(EEquipmentSlot Slot, AItem* Item);

	UFUNCTION(BlueprintCallable)
	bool TryUnequip(EEquipmentSlot Slot, bool bIsSwap = false);

	int GetTotalArmor() const;
};
