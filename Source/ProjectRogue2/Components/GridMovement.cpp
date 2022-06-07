// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMovement.h"
#include "../Characters/BaseCharacter.h"

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
	Position.X = FMath::RoundToZero(Position.X);
	Position.Y = FMath::RoundToZero(Position.Y);
	Position.Z = FMath::RoundToZero(Position.Z);
	NextPosition.SetLocation(Position);
	//starting north will help us 
	FacingDirection = ECompass::North;
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
			switch (FacingDirection)
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
			switch (FacingDirection)
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
	Position.X = FMath::RoundToZero(Position.X);
	Position.Y = FMath::RoundToZero(Position.Y);
	Position.Z = FMath::RoundToZero(Position.Z);
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
		switch (FacingDirection)
		{
			case ECompass::North: FacingDirection = ECompass::West; break;
			case ECompass::South: FacingDirection = ECompass::East; break;
			case ECompass::East:  FacingDirection = ECompass::North; break;
			case ECompass::West:  FacingDirection = ECompass::South; break;
		}
		auto Rotation = GetOwner()->GetActorRotation();
		Rotation.Yaw -= 90;
		NextPosition.SetRotation(Rotation.Quaternion());
		IsActive = true;
	}
	else if (Direction == EDirection::Right)
	{
		switch (FacingDirection)
		{
			case ECompass::North: FacingDirection = ECompass::East; break;
			case ECompass::South: FacingDirection = ECompass::West; break;
			case ECompass::East:  FacingDirection = ECompass::South; break;
			case ECompass::West:  FacingDirection = ECompass::North; break;
		}
		auto Rotation = GetOwner()->GetActorRotation();
		Rotation.Yaw += 90;
		NextPosition.SetRotation(Rotation.Quaternion());
		IsActive = true;
	}
}

void UGridMovement::Motion()
{
	auto Position = Owner->GetActorLocation();
	auto Next = NextPosition.GetLocation();
	//round to zero to avoid comparisons like 260.4 == 260.0
	Position.X = FMath::RoundToZero(Position.X);
	Position.Y = FMath::RoundToZero(Position.Y);
	Position.Z = FMath::RoundToZero(Position.Z);
	Next.X = FMath::RoundToZero(Next.X);
	Next.Y = FMath::RoundToZero(Next.Y);
	Next.Z = FMath::RoundToZero(Next.Z);

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
			Offset.X = FMath::RoundToZero(Offset.X);
			Offset.Y = FMath::RoundToZero(Offset.Y);
			Owner->AddActorWorldOffset(Offset);
		}
	}
	else 
	{
		//using a nested if avoids creating these if we arent turning
		auto Rotation = Owner->GetActorRotation();
		auto Rotator = NextPosition.Rotator();
		Rotation.Yaw = FMath::RoundToZero(Rotation.Yaw);
		Rotator.Yaw = FMath::RoundToZero(Rotator.Yaw);
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
		}
	}

}