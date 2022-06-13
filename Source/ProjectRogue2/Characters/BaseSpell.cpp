// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpell.h"
#include "BaseCharacter.h"
#include "../Components/CharacterStats.h"

// Sets default values
ABaseSpell::ABaseSpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseSpell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseSpell::CastSpell(ABaseCharacter* pCaster, ABaseCharacter* pTarget)
{
    Caster = pCaster;
    if (Damage > 0)
    {
        OnSpellCasted(pTarget);
    }
    else if (Healing > 0)
    {
        OnHealCasted();
    }
}

int ABaseSpell::GetDamage() const
{
    return Damage + GetIntelligence();
}

int ABaseSpell::GetHealing() const
{
    return Healing + GetIntelligence();
}

int ABaseSpell::GetIntelligence() const
{
    UActorComponent* pComponent = Caster->GetComponentByClass(UCharacterStats::StaticClass());
    if (!pComponent)
    {
        return false;
    }
    UCharacterStats* pStats = Cast<UCharacterStats>(pComponent);
    const float intelligence = pStats->GetStat(EStats::Intelligence);
    return static_cast<int>(intelligence);
}