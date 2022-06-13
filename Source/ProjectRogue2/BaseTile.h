// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Characters/BaseCharacter.h"

#include "BaseTile.generated.h"

UCLASS()
class PROJECTROGUE2_API ABaseTile : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Tile")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, Category = "Tile")
	UBoxComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile")
	ABaseCharacter* CharacterOnTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	int32 TileSize;


public:	
	// Sets default values for this actor's properties
	ABaseTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	int32 GetTileSize() const { return TileSize; }
	ABaseCharacter* GetCharacterOnTile() const { return CharacterOnTile; }
	void SetCharacterOnTile(ABaseCharacter* NewCharacter) { CharacterOnTile = NewCharacter; }
};
