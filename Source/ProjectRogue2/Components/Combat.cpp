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
	StartingHealth = 0;
	StartingMana = 0;
	MeleeRange = 0;
	// ...
}


// Called when the game starts
void UCombat::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Owner = Cast<ABaseCharacter>(GetOwner());
	CurrentHealth = MaxHealth = StartingHealth;
	CurrentMana = MaxMana = StartingMana;
}

void UCombat::Attack(FString& LogMessage, ABaseCharacter* Target)
{
	int Damage = 0;
	int Range = MeleeRange;
	UEquipment* pEquipment = Owner->GetComponent<UEquipment>();
	if (pEquipment)
	{
		Range += pEquipment->GetRange();
		Damage += pEquipment->GetWeaponDamage();
	}

	UCharacterStats* pStat = Owner->GetComponent<UCharacterStats>();
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
		UCombat* pCombat = Target->GetComponent<UCombat>();
		if (pCombat)
		{
			pCombat->TakeDamage(Damage);
			FString Log = Owner->GetCharacterName();
			Log.Append(" attacked ");
			Log.Append(Target->GetCharacterName());
			Log.Append(" for ");
			Log.Append(FString::FromInt(Damage));
			Log.Append(" damage.");
			LogMessage = Log;
		}
	}
	else
	{
		//LOG
	}
}

void UCombat::CastSpell(ABaseSpell* Spell, ABaseCharacter* Target)
{
	Spell->CastSpell(Owner, Target);
}

void UCombat::TakeDamage(int Amount)
{
	//get armor
	UActorComponent* pComponent = Owner->GetComponentByClass(UEquipment::StaticClass());
	UEquipment* pEquipment = Cast<UEquipment>(pComponent); 
	int Armor = 0;
	if (pEquipment)
	{
		pEquipment->GetTotalArmor();
	}

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