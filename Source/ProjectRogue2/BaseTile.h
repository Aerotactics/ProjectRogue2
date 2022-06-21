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
	UFUNCTION(BlueprintCallable, Category = "Tile")
	void SetCharacterOnTile(ABaseCharacter* NewCharacter) { CharacterOnTile = NewCharacter; }

	//This was set up so that way characters moving away from tiles would be detected by the tile
	// but Michael noted how that can just be done in GridMovement, so this is commented out for 
	// now because we dont need it yet, but I don't want to track down this code again
	//UFUNCTION()
	//void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//UFUNCTION()
	//void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
