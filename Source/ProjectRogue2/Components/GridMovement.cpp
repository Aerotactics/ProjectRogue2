// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMovement.h"
#include "../Characters/BaseCharacter.h"
#include "../BaseTile.h"

// Sets default values for this component's properties
UGridMovement::UGridMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.01f;
	MoveDistance = 100;
	StepsPerTick = 5;
	RotationsPerTick = 1;
	Owner = nullptr;
	IsActive = false;
	// ...
}


// Called when the game starts
void UGridMovement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Owner = Cast<ABaseCharacter>(GetOwner());
	//cache character transform so that NextPosition isnt 0
	NextPosition = Owner->GetActorTransform();
	auto Position = Owner->GetActorLocation();
	//round all the values because we're dealing with decimals
	Position.X = FMath::RoundHalfToEven(Position.X);
	Position.Y = FMath::RoundHalfToEven(Position.Y);
	Position.Z = FMath::RoundHalfToEven(Position.Z);
	NextPosition.SetLocation(Position);
}


// Called every frame
void UGridMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsActive)
	{
		return;
	}

	Motion();
}

void UGridMovement::Move(EDirection Direction)
{
	if (IsActive)
	{
		//LOG
		return;
	}

	DirectionToMove = Direction;
	auto ForwardVector = Owner->GetActorForwardVector();
	auto RightVector = Owner->GetActorRightVector();
	FVector Offset(0.f, 0.f, 0.f);
	switch (Direction)
	{
		case EDirection::Forward: 
		{
			Offset = ForwardVector * MoveDistance;
		}
		break;
		case EDirection::Backward:
		{
			Offset = (ForwardVector * -1) * MoveDistance;
		}
		break;
		case EDirection::Left:	  
		{
			switch (GetFacingDirection())
			{
				case ECompass::North: Offset.X = MoveDistance * -1; break;
				case ECompass::South: Offset.X = MoveDistance;		break;
				case ECompass::East:  Offset.Y = MoveDistance * -1;	break;
				case ECompass::West:  Offset.Y = MoveDistance;		break;
			}
		}
		break;
		case EDirection::Right:   
		{
			switch (GetFacingDirection())
			{
				case ECompass::North: Offset.X = MoveDistance;		break;
				case ECompass::South: Offset.X = MoveDistance * -1;	break;
				case ECompass::East:  Offset.Y = MoveDistance;		break;
				case ECompass::West:  Offset.Y = MoveDistance * -1;	break;
			}
		}
		break;
	}

	auto Position = Owner->GetActorLocation() + Offset;
	Position.X = FMath::RoundHalfToEven(Position.X);
	Position.Y = FMath::RoundHalfToEven(Position.Y);
	Position.Z = FMath::RoundHalfToEven(Position.Z);

	//line trace the tile before moving so we dont move to a tile another character is moving to
	FHitResult HitResult;
	FVector Start = Owner->GetActorLocation();
	FCollisionObjectQueryParams ObjectParams;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Owner);
	GetWorld()->LineTraceSingleByObjectType(HitResult, Start, Position, ObjectParams, QueryParams);
	if (HitResult.Actor.IsValid())
	{
		ABaseTile* Tile = Cast<ABaseTile>(HitResult.Actor);
		if (Tile->GetCharacterOnTile())
		{
			//if there is a character already on the tile we're trying to move to, we cant move
			return;
		}
		Tile->SetCharacterOnTile(Owner);
	}

	NextPosition.SetLocation(Position);
	IsActive = true;
}

void UGridMovement::Turn(EDirection Direction)
{
	if (IsActive)
	{
		//LOG
		return;
	}

	DirectionToMove = Direction;
	if (Direction == EDirection::Left)
	{
		auto Rotation = GetOwner()->GetActorRotation();
		Rotation.Yaw -= 90;
		NextPosition.SetRotation(Rotation.Quaternion());
		IsActive = true;
	}
	else if (Direction == EDirection::Right)
	{
		auto Rotation = GetOwner()->GetActorRotation();
		Rotation.Yaw += 90;
		NextPosition.SetRotation(Rotation.Quaternion());
		IsActive = true;
	}
}

////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////

ECompass UGridMovement::GetFacingDirection()
{
	FVector ForwardVector = Owner->GetActorForwardVector();
	ForwardVector.X = FMath::RoundHalfToEven(ForwardVector.X);
	ForwardVector.Y = FMath::RoundHalfToEven(ForwardVector.Y);
	if (ForwardVector.X == 1 && ForwardVector.Y == 0)
	{
		return ECompass::East;
	}
	else if (ForwardVector.X == -1 && ForwardVector.Y == 0)
	{
		return ECompass::West;
	}
	else if (ForwardVector.X == 0 && ForwardVector.Y == 1)
	{
		return ECompass::South;
	}
	else if (ForwardVector.X == 0 && ForwardVector.Y == -1)
	{
		return ECompass::North;
	}
	
	return ECompass::Diagonal;
}

void UGridMovement::Motion()
{
	auto Position = Owner->GetActorLocation();
	auto Next = NextPosition.GetLocation();
	//round to zero to avoid comparisons like 260.4 == 260.0
	Position.X = FMath::RoundHalfToEven(Position.X);
	Position.Y = FMath::RoundHalfToEven(Position.Y);
	Position.Z = FMath::RoundHalfToEven(Position.Z);
	Next.X = FMath::RoundHalfToEven(Next.X);
	Next.Y = FMath::RoundHalfToEven(Next.Y);
	Next.Z = FMath::RoundHalfToEven(Next.Z);

	if ((Position.X != Next.X) || (Position.Y != Next.Y))
	{
		auto ForwardVector = Owner->GetActorForwardVector();
		switch (DirectionToMove)
		{
			case EDirection::Backward:  ForwardVector *= -1;					 break;
			case EDirection::Right:
			case EDirection::Left:		
			{
				auto Difference = Next - Position;
				Difference.Normalize();
				ForwardVector = Difference;
			}
		}

		if (FVector::Distance(Position, Next) < StepsPerTick)
		{
			Owner->SetActorLocation(Next);
		}
		else
		{
			auto Offset = ForwardVector * StepsPerTick;
			Offset.X = FMath::RoundHalfToEven(Offset.X);
			Offset.Y = FMath::RoundHalfToEven(Offset.Y);
			Owner->AddActorWorldOffset(Offset);
		}
	}
	else 
	{
		//using a nested if avoids creating these if we arent turning
		auto Rotation = Owner->GetActorRotation();
		auto Rotator = NextPosition.Rotator();
		Rotation.Yaw = FMath::RoundHalfToEven(Rotation.Yaw);
		Rotator.Yaw = FMath::RoundHalfToEven(Rotator.Yaw);
		if (Rotation.Yaw != Rotator.Yaw)
		{
			if (DirectionToMove == EDirection::Left)
			{
				Owner->AddControllerYawInput(RotationsPerTick * -1);
			}
			else if (DirectionToMove == EDirection::Right)
			{
				Owner->AddControllerYawInput(RotationsPerTick);
			}
		}
		else
		{
			//first we check if the character is moving
			//then we check if the character is turning
			//if neither, the character isnt active
			IsActive = false;
			Position = Owner->GetActorLocation();
			GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, FString::Printf(TEXT("X: %f, Y: %f"), Position.X, Position.Y));
		}
	}

}