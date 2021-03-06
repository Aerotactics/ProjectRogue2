// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/BaseCharacter.h"
#include "Components/CharacterStats.h"
#include "Components/Equipment.h"
#include "Item.generated.h"

UENUM()
enum class EItemRarity
{
	Normal,
	Magic,
	Relic,
	Legendary
};

USTRUCT(Blueprintable)
struct FStatEffect
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	EStats Stat;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float Amount;
};

UCLASS()
class PROJECTROGUE2_API AItem : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CustomName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemRarity Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LevelRequirement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStats StatType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StatLevelRequirement;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Durability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentSlot EquipSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStatEffect> Effects;
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Item")
	const TArray<FStatEffect>& GetStatEffects() const { return Effects; }

	UFUNCTION(BlueprintCallable, Category = "Item")
	EEquipmentSlot GetEquipSlot() { return EquipSlot; }

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(ABaseCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnEquipped(ABaseCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUnequipped(ABaseCharacter* Character);

	void OnEquip(ABaseCharacter* Character);
	void OnUnequip(ABaseCharacter* Character);

	const FString& GetCustomName() const { return CustomName; }
	const FString& GetItemName() const { return ItemName; }
	const FString& GetDescription() const { return Description; }
	EItemRarity GetRarity() const { return Rarity; }
	int32 GetLevelRequirement() const { return LevelRequirement; }
	int32 GetStatLevelRequirement() const { return StatLevelRequirement; }
	int32 GetDamage() const { return Damage; }
	int32 GetDurabiliy() const { return Durability; }
	int32 GetArmor() const { return Armor; }
	int32 GetRange() const { return Range; }
	int32 GetMaxStackSize() const { return MaxStackSize; }
	EStats GetStatType() const { return StatType; }
	EEquipmentSlot GetEquipSlot() const { return EquipSlot; }
};
