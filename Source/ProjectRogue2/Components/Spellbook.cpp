// Fill out your copyright notice in the Description page of Project Settings.


#include "Spellbook.h"
#include "../Components/CharacterStats.h"

// Sets default values for this component's properties
USpellbook::USpellbook()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpellbook::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
    Owner = Cast<ABaseCharacter>(GetOwner());
}


// Called every frame
void USpellbook::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USpellbook::AddSpell(ABaseSpell* Spell)
{
    UActorComponent* pComponent = Owner->GetComponentByClass(UCharacterStats::StaticClass());
    if (!pComponent)
    {
        return false;
    }
    UCharacterStats* pStats = Cast<UCharacterStats>(pComponent);
    const float intelligence = pStats->GetStat(EStats::Intelligence);
    const int Requirement = Spell->GetIntelligenceRequirement();
    if (intelligence < Requirement)
    {
        int Difference = Requirement - intelligence;
        GEngine->AddOnScreenDebugMessage(-1, 12, FColor::Red, FString::Printf(TEXT("%s needs %d more intelligence to learn %s"), *Owner->GetCharacterName(), Difference, *Spell->GetSpellName()));
        return false;
    }

    Spells.Add(Spell);
    return true;
}

bool USpellbook::HasSpell(const FString& Name) const
{
    for (const auto& Spell : Spells)
    {
        if (Spell->GetName() == Name)
        {
            return true;
        }
    }
    return false;
}

ABaseSpell* USpellbook::GetSpell(const FString& Name) const
{
    for (const auto& Spell : Spells)
    {
        if (Spell->GetName() == Name)
        {
            return Spell;
        }
    }
    return nullptr;
}