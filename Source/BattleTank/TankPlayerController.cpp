// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
	if (ATankPlayerController::GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("We have a possessed: %s"), *(GetControlledTank()->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No tank found..."));
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair(); //TODO
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank)
	{
		return;
	}
	else {
		//Get world location if linetrace through crosshair
		//If it hits the landscape
			//Tell controlled tank to aim this point
	}
}