// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSpell.generated.h"

class ABaseCharacter;

UCLASS()
class PROJECTROGUE2_API ABaseSpell : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell")
	ABaseCharacter* Caster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	int Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	int Healing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	int Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	int Cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	int Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	int IntelligenceRequirement;
	
public:	
	// Sets default values for this actor's properties
	ABaseSpell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Spell")
	void OnSpellCasted(ABaseCharacter* pTarget);
	UFUNCTION(BlueprintImplementableEvent, Category = "Spell")
	void OnHealCasted();

	void CastSpell(ABaseCharacter* pCaster, ABaseCharacter* pTarget);

	const FString& GetSpellName() const { return Name; }
	int GetManaCost() const { return Cost; }
	int GetCooldown() const { return Cooldown; }
	int GetRange() const { return Range; }
	int GetIntelligenceRequirement() const { return IntelligenceRequirement; }
	int GetDamage() const;
	int GetHealing() const;

private:
	int GetIntelligence() const;
};
