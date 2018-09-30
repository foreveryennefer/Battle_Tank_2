// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "../Public/TankAIController.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));
	auto PlayerTank = GetPawn();

	if (ensure(PlayerTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("AI has found player: %s"), *(PlayerTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AI controller cannot find player tank."));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(AimingComponent || PlayerTank || ControlledTank)) { return; }
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

	// Aim towards the player
	FVector PlayerLocation = PlayerTank->GetActorLocation();
	AimingComponent->AimAt(PlayerLocation);

	// Fire if ready
	//AimingComponent->Fire(); // TODO limit firing rate
	
}





