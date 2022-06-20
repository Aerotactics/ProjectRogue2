// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectRogue2GameMode.generated.h"

class ABaseTile;
class ABaseCharacter;

UCLASS(minimalapi)
class AProjectRogue2GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> UnavailableTileLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ABaseCharacter>> Monsters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnemyCount;

public:
	AProjectRogue2GameMode();
	
	UFUNCTION(BlueprintCallable, Category = "World")
	void GenerateFloor(TSubclassOf<ABaseTile> TileClass, FVector StartPosition, int32 TilesWide, int32 TilesLong, TArray<ABaseTile*>& SpawnedTiles);

	UFUNCTION(BlueprintCallable, Category = "World")
	void GenerateMonsters(const FVector& StartLocation, const TArray<ABaseTile*>& Tiles, int32 MonstersToSpawn, bool bDoMonstersMove);

private:
	bool CheckIsAvailable(const FVector& TraceEnd);
	TSubclassOf<ABaseCharacter> GetRandomMonster() const;
	void SpawnNewMonster(const FVector& StartLocation, const TArray<ABaseTile*>& Tiles, bool bDoMonstersMove);
};
