// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "../Public/TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));
	auto PlayerTank = GetPlayerTank();

	if (ensure(PlayerTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("AI has found player: %s"), *(PlayerTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AI controller cannot find player tank."));
	}
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerPawn)) {
		return nullptr;
	}
	else {
		return Cast<ATank>(PlayerPawn);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) {
		// Move towards the player
		MoveToActor(GetPlayerTank(), AcceptanceRadius); // TODO check radius is in cm

		// Aim towards the player
		FVector PlayerLocation = GetPlayerTank()->GetActorLocation();
		GetAITank()->AimAt(PlayerLocation);

		// Fire if ready
		GetAITank()->Fire(); // TODO limit firing rate
	}
}

ATank* ATankAIController::GetAITank() const
{
	return Cast<ATank>(GetPawn());
}




