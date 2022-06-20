// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTile.h"

// Sets default values
ABaseTile::ABaseTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	SetRootComponent(StaticMesh);
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(StaticMesh);
<<<<<<< Updated upstream
=======
	//Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseTile::OnOverlapBegin);
	//Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseTile::OnOverlapEnd);
>>>>>>> Stashed changes
}

// Called when the game starts or when spawned
void ABaseTile::BeginPlay()
{
	Super::BeginPlay();
	
}
<<<<<<< Updated upstream
=======

//void ABaseTile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	CharacterOnTile = Cast<ABaseCharacter>(OtherActor);
//}

//void ABaseTile::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	CharacterOnTile = nullptr;
//}
>>>>>>> Stashed changes
