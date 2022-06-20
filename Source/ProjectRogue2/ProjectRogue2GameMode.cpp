// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectRogue2GameMode.h"
#include "ProjectRogue2HUD.h"
#include "ProjectRogue2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "BaseTile.h"
#include "Components/GridMovement.h"
#include "Components/Combat.h"
#include "Components/Equipment.h"

AProjectRogue2GameMode::AProjectRogue2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProjectRogue2HUD::StaticClass();
}

void AProjectRogue2GameMode::GenerateFloor(TSubclassOf<ABaseTile> TileClass, FVector StartPosition, int32 TilesWide, int32 TilesLong, TArray<ABaseTile*>& SpawnedTiles)
{
	auto Defaults = TileClass->GetDefaultObject();
	ABaseTile* TileDefaults = Cast<ABaseTile>(Defaults);
	int32 TileSize = TileDefaults->GetTileSize();
	FTransform Transform;
	for (int32 rows = 0; rows < TilesLong; ++rows)
	{
		for (int32 columns = 0; columns < TilesWide; ++columns)
		{
			int32 xOffset = columns * TileSize;
			int32 yOffset = rows * TileSize;
			FVector Position = StartPosition;
			Position.X += xOffset;
			Position.Y += yOffset;
			Transform.SetLocation(Position);
			ABaseTile* Tile = GetWorld()->SpawnActor<ABaseTile>(TileClass, Transform);
			SpawnedTiles.Add(Tile);
		}
	}
}

void AProjectRogue2GameMode::GenerateMonsters(const FVector& StartLocation, const TArray<ABaseTile*>& Tiles, int32 MonstersToSpawn, bool bDoMonstersMove)
{
	UWorld* World = GetWorld();
	AActor* ActorOnTile = nullptr;
	TSubclassOf<ABaseCharacter> MonsterClass = nullptr;
	ABaseCharacter* Monster = nullptr;
	int32 EnemiesSpawned = 0;
	int32 RandomTileIndex = 0;
	int32 RandomMonsterIndex = 0;
	FVector TilePosition;
	FVector TraceDistance{ 0.f, 0.f, 150.f };
	FVector TraceEnd;
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	FCollisionObjectQueryParams Params;
	Params.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	Params.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);

	TArray<ABaseTile*> AvailableTiles;
	//T: cache available tiles so they're easier to randomly select
	//and can be removed from the array
	for (auto& Tile : Tiles)
	{
		//line trace up from tile
		TilePosition = Tile->GetActorLocation();
		TraceEnd = TilePosition + TraceDistance;
		QueryParams.AddIgnoredActor(Tile);
		World->LineTraceSingleByObjectType(HitResult, TilePosition, TraceEnd, Params, QueryParams);
		ActorOnTile = Cast<AActor>(HitResult.Actor);

		//check if location is available
		if (!CheckIsAvailable(TilePosition))
			continue;

		if (!ActorOnTile)
		{
			AvailableTiles.Add(Tile);
		}
		QueryParams.ClearIgnoredActors();
	}

	ABaseTile* Tile = nullptr;
	int32 MonsterCount = Monsters.Num() - 1;
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	while (EnemiesSpawned < MonstersToSpawn)
	{
		//find a random tile
		RandomTileIndex = FMath::RandRange(0, AvailableTiles.Num() - 1);
		Tile = AvailableTiles[RandomTileIndex];

		//line trace up from tile
		TilePosition = Tile->GetActorLocation();
		TraceEnd = TilePosition + TraceDistance;
		QueryParams.AddIgnoredActor(Tile);
		World->LineTraceSingleByObjectType(HitResult, TilePosition, TraceEnd, Params, QueryParams);
		ActorOnTile = Cast<AActor>(HitResult.Actor);

		//if there is no building or monster, spawn monster
		if (!ActorOnTile)
		{
			//get random monster class
			RandomMonsterIndex = FMath::RandRange(0, MonsterCount);
			MonsterClass = Monsters[RandomMonsterIndex];

			//lower monster spawn positions so they line up with tiles
			//TraceEnd.Z = FMath::TruncToInt(StartLocation.Z);
			//create monster from class
			Monster = World->SpawnActor<ABaseCharacter>(MonsterClass, TraceEnd, FRotator(0.f, 0.f, 0.f), SpawnParams);			

			UCombat* pCombat = NewObject<UCombat>(Monster);
			pCombat->SetDeathCallback([this, StartLocation, AvailableTiles, bDoMonstersMove]
				{ SpawnNewMonster(StartLocation, AvailableTiles, bDoMonstersMove); });
			Monster->AddComponent("Combat", false, FTransform(), pCombat);
			Monster->AddComponentByClass(UEquipment::StaticClass(), false, FTransform(), false);
			if (bDoMonstersMove)
			{
				Monster->AddComponentByClass(UGridMovement::StaticClass(), false, FTransform(), false);				
			}

			++EnemiesSpawned;
		}

		//remove the tile so we dont randomly select it again
		AvailableTiles.Remove(Tile);
		QueryParams.ClearIgnoredActors();
	}
}

bool AProjectRogue2GameMode::CheckIsAvailable(const FVector& TraceEnd)
{
	for (const auto& Location : UnavailableTileLocations)
	{
		if (TraceEnd == Location)
		{
			return false;
		}
	}
	return true;
}

void AProjectRogue2GameMode::SpawnNewMonster(const FVector& StartLocation, const TArray<ABaseTile*>& Tiles, bool bDoMonstersMove)
{
	GenerateMonsters(StartLocation, Tiles, 1, bDoMonstersMove);
}

TSubclassOf<ABaseCharacter> AProjectRogue2GameMode::GetRandomMonster() const
{
	check(Monsters.Num() > 0);
	return Monsters[FMath::RandRange(0, Monsters.Num() - 1)];
}
