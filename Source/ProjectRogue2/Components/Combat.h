// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "GenericPlatform/GenericPlatformMisc.h"

#include "Combat.generated.h"

class ABaseCharacter;
class ABaseSpell;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTROGUE2_API UCombat : public UActorComponent
{
	GENERATED_BODY()

private:
	ABaseCharacter* Owner;
	ABaseCharacter* Target;
	TFunction<void()> Callback;
	int CurrentHealth;
	int MaxHealth;
	int CurrentMana;
	int MaxMana;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	int32 MeleeRange;

public:	
	// Sets default values for this component's properties
	UCombat();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Attack();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void CastSpell(ABaseSpell* Spell);

	void SetTarget(ABaseCharacter* NewTarget) { Target = NewTarget; }
	void SetDeathCallback(TFunction<void()> NewCallback) { Callback = NewCallback; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TakeDamage(int Amount);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Heal(int Amount);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RestoreMana(int Amount);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ReduceMana(int Amount);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void IncreaseMaxHealth(int Amount) { MaxHealth += Amount; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void IncreaseMaxMana(int Amount) { MaxMana += Amount; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ReduceMaxHealth(int Amount) { MaxHealth -= Amount; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ReduceMaxMana(int Amount) { MaxMana -= Amount; }

	ABaseCharacter* GetTarget() const { return Target; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	int GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	int GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	int GetCurrentMana() const { return CurrentMana; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	int GetMaxMana() const { return MaxMana; }

	bool IsDead() const { return CurrentHealth == 0; }
};
