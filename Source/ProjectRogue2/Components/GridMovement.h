// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Engine/EngineTypes.h"

#include "GridMovement.generated.h"

UENUM()
enum class EDirection : uint8
{
	Forward,
	Backward,
	Left,
	Right,
};

UENUM()
enum class ECompass : uint8
{
	North,
	South,
	East,
	West,
	Diagonal,
};

class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTROGUE2_API UGridMovement : public UActorComponent
{
	GENERATED_BODY()

private:
	ABaseCharacter* Owner;
	FTransform NextPosition;
	EDirection DirectionToMove;
	bool IsActive;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Distance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int32 StepsPerTick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int32 RotationsPerTick;

public:	
	// Sets default values for this component's properties
	UGridMovement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//step1: linear movement
	//step2: easing movement

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Move(EDirection Direction);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Turn(EDirection Direction);

	UFUNCTION(BlueprintCallable, BlueprintPure , Category = "Movement")
	ABaseCharacter* GetBaseCharacter() const { return Owner; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement")
	ECompass GetFacingDirection();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement")
	FVector GetInteractPosition(FVector Direction);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FHitResult Interact(FVector InteractPosition);

	float GetMovementDistance() const { return Distance; }

private:
	void Motion();
};
