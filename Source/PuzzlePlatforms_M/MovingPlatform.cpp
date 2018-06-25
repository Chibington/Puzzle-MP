// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"



AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}


void AMovingPlatform::AddActiveTrigger()
{
	activeTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (activeTriggers > 0)
	{
		activeTriggers--;
	}
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}	

	globalStartLocation = GetActorLocation();
	globalTargetLocation = GetTransform().TransformPosition(targetLoc); //takes the local target location and transforms it into a global one
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (activeTriggers > 0)
	{
		if (HasAuthority())
		{
			FVector loc = GetActorLocation(); //Gets the actors global location
			float journeyLength = (globalTargetLocation - globalStartLocation).Size(); //magnitude of the vector
			float journeyTravelled = (loc - globalStartLocation).Size();
			if (journeyTravelled >= journeyLength)
			{
				FVector swap = globalStartLocation;
				globalStartLocation = globalTargetLocation;
				globalTargetLocation = swap;
			}
			FVector direction = (globalTargetLocation - globalStartLocation).GetSafeNormal(); //Normalizes (unit vector) the direction from the target location to the current actor location
			loc += speed * direction * DeltaTime; //changes the actors location by adding a multiplication of the speed, direction, and time
			SetActorLocation(loc);
		}
	}

	

	
}
