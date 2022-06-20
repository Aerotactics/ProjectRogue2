// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat.h"
#include "../Characters/BaseCharacter.h"
#include "../Characters/BaseSpell.h"
#include "../Item.h"
#include "CharacterStats.h"
#include "Equipment.h"

// Sets default values for this component's properties
UCombat::UCombat()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombat::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Owner = Cast<ABaseCharacter>(GetOwner());
}

void UCombat::Attack()
{
<<<<<<< Updated upstream
	UActorComponent* pComponent = nullptr;
	pComponent = Owner->GetComponentByClass(UEquipment::StaticClass());
	check(pComponent);
	UEquipment* pEquipment = Cast<UEquipment>(pComponent);
	check(pEquipment);
	int Damage = pEquipment->GetWeaponDamage();
	int Range = pEquipment->GetRange();
	pComponent = Owner->GetComponentByClass(UCharacterStats::StaticClass());
	check(pComponent);
	UCharacterStats* pStat = Cast<UCharacterStats>(pComponent);
=======
	int Damage = 0;
	int Range = MeleeRange;
	UEquipment* pEquipment = Owner->GetComponent<UEquipment>();
	if (pEquipment)
	{
		Range += pEquipment->GetRange();
		Damage += pEquipment->GetWeaponDamage();
	}

	UCharacterStats* pStat = Owner->GetComponent<UCharacterStats>();
>>>>>>> Stashed changes
	check(pStat);

	if (Range == MeleeRange)
	{
		Damage += pStat->GetStat(EStats::Strength);
	}
	else
	{
		Damage += pStat->GetStat(EStats::Dexterity);
	}

	//FHitResult HitResult;
	//FVector Start = Owner->GetActorLocation();
	//FVector End = Start + (Owner->GetActorForwardVector() * Range);
	//FCollisionObjectQueryParams ObjectParams;
	//FCollisionQueryParams QueryParams;
	//QueryParams.AddIgnoredActor(Owner);
	//Owner->GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ObjectParams, QueryParams);

	if (ABaseCharacter* pTarget = Cast<ABaseCharacter>(Target))
	{
		pComponent = pTarget->GetComponentByClass(UCombat::StaticClass());
		UCombat* pCombat = Cast<UCombat>(pComponent);
		if (pCombat)
		{
			pCombat->TakeDamage(Damage);
		}
	}
	else
	{
		//LOG
	}
}

void UCombat::CastSpell(ABaseSpell* Spell)
{
	Spell->CastSpell(Owner, Target);
}

void UCombat::TakeDamage(int Amount)
{
	//get armor
	UActorComponent* pComponent = Owner->GetComponentByClass(UEquipment::StaticClass());
	UEquipment* pEquipment = Cast<UEquipment>(pComponent); 
	int Armor = pEquipment->GetTotalArmor();

	int Damage = (Amount - Armor);
	//make sure that at least 1 damage is always dealt
	if (Damage <= 0)
	{
		Damage = 1;
	}
	CurrentHealth -= Damage;
	if (CurrentHealth < 0)
	{
		CurrentHealth = 0;
	}
}

void UCombat::Heal(int Amount)
{
	UActorComponent* pComponent = Owner->GetComponentByClass(UCharacterStats::StaticClass());
	UCharacterStats* pStats = Cast<UCharacterStats>(pComponent);
	CurrentHealth += Amount + pStats->GetStat(EStats::Intelligence);
	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

void UCombat::RestoreMana(int Amount)
{
	CurrentMana += Amount;
	if (CurrentMana > MaxMana)
	{
		CurrentMana = MaxMana;
	}
}

void UCombat::ReduceMana(int Amount)
{
	CurrentMana -= Amount;
	if (CurrentMana < 0)
	{
		CurrentMana = 0;
	}
}