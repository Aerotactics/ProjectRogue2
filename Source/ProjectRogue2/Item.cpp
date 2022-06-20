// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Characters/BaseCharacter.h"
#include "Components/Equipment.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Effects = TArray<FStatEffect>();
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnEquip(ABaseCharacter* Character, EEquipmentSlot Slot)
{
	UActorComponent* Component = Character->GetComponentByClass(UCharacterStats::StaticClass());
	UCharacterStats* StatComponent = Cast<UCharacterStats>(Component);
	if (StatComponent != nullptr)
	{
		for (auto& StatEffect : Effects)
		{
			StatComponent->Increase(StatEffect.Stat, StatEffect.Amount);
		}
		OnEquipped(Character);
	}
<<<<<<< Updated upstream
=======
	OnEquipped(Character, Slot);
>>>>>>> Stashed changes
}

void AItem::OnUnequip(ABaseCharacter* Character, EEquipmentSlot Slot)
{
	UActorComponent* Component = Character->GetComponentByClass(UCharacterStats::StaticClass());
	UCharacterStats* StatComponent = Cast<UCharacterStats>(Component);
	if (StatComponent != nullptr)
	{
		for (auto& StatEffect : Effects)
		{
			StatComponent->Decrease(StatEffect.Stat, StatEffect.Amount);
		}
		OnUnequipped(Character);
	}
<<<<<<< Updated upstream
=======
	OnUnequipped(Character, Slot);
>>>>>>> Stashed changes
}