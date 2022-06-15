// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "../BaseTile.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FVector Start = GetActorLocation();
	FVector End = Start;
	Start.Z -= 100;

	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	FCollisionQueryParams QueryParams;
	GetWorld()->DebugDrawTraceTag = QueryParams.TraceTag;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ObjectParams, QueryParams);
	if (ABaseTile* Tile = Cast<ABaseTile>(HitResult.Actor))
	{
		Tile->SetCharacterOnTile(this);
		TileImOn = Tile;
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

