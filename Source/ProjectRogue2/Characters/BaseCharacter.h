// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UENUM()
enum class Gender : uint8
{
	Male,
	Female,
	NonBinary,
	Agender,
	GenderQueer,
	Androgynous,
	Transgender
};

UCLASS()
class PROJECTROGUE2_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	Gender Gender;

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Character")
	const FString& GetCharacterName() const { return Name; }
};
