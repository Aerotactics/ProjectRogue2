// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
/*

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterClass.generated.h"

UENUM()
enum class EClass
{
	Warrior,
	Rogue,
	Paladin,
	Cleric,
	Mage,
	Warlock,
	Hunter,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTROGUE2_API UCharacterClass : public UActorComponent
{
	GENERATED_BODY()

private:
	EClass CharacterClass;
	int Level;
	int Experience;
	int RequiredExperience;
	float RequiredExperienceMultiplier;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int StatPointsPerLevel;

public:	
	// Sets default values for this component's properties
	UCharacterClass();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "CharacterClass")
	void GainExperience(const int Amount);

	UFUNCTION(BlueprintCallable, Category = "CharacterClass")
	void LoseExperience(const int Amount);

	UFUNCTION(BlueprintCallable, Category = "CharacterClass")
	void SetLevel(int NewLevel) { Level = NewLevel; }

	UFUNCTION(BlueprintCallable, Category = "CharacterClass")
	int GetLevel() const { return Level; }

	void IncreaseExperienceRequiredPerLevel(float Rate) { RequiredExperienceMultiplier += Rate; }
	void SetRequiredExperienceMultiplier(float Rate) { RequiredExperienceMultiplier = Rate; }

	EClass GetCharacterClass() const { return CharacterClass; }
	int GetExperience() const { return Experience; }
	int GetRequiredExperience() const { return RequiredExperience; }
	int GetRequiredExperienceMultiplier() const { return RequiredExperienceMultiplier; }
};
*/