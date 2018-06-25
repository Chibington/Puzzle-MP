// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_M_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	UPROPERTY(EditAnywhere)
		float speed = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stuff", Meta = (MakeEditWidget = true))
		FVector targetLoc;

	void AddActiveTrigger();
	void RemoveActiveTrigger();


protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	

private:
	FVector globalTargetLocation;
	FVector globalStartLocation;

	UPROPERTY(EditAnywhere)
		int32 activeTriggers = 1;
};
