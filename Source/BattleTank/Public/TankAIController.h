// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TankAIController.generated.h"

// Forward declaration
class ATank;
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// How close can the AI tank get to player
	float AcceptanceRadius = 3000.f;
};
