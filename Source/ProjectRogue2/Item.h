// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/BaseCharacter.h"
#include "Components/CharacterStats.h"
#include "Equipment.h"
#include "Item.generated.h"

UCLASS()
class PROJECTROGUE2_API AItem : public AActor
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CustomName;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

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
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentSlot EquipSlot;
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	EEquipmentSlot GetEquipSlot() { return EquipSlot; }

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(ABaseCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnEquip(ABaseCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUnequip(ABaseCharacter* Character);
};
