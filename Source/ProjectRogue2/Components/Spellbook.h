// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "../Characters/BaseSpell.h"
#include "../Characters/BaseCharacter.h"

#include "Spellbook.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTROGUE2_API USpellbook : public UActorComponent
{
	GENERATED_BODY()

protected:
	ABaseCharacter* Owner;
	TArray<ABaseSpell*> Spells;

public:	
	// Sets default values for this component's properties
	USpellbook();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool AddSpell(ABaseSpell* Spell);
	bool HasSpell(const FString& Name) const;
	ABaseSpell* GetSpell(const FString& Name) const;
	const TArray<ABaseSpell*> GetSpells() const { return Spells; }
};
