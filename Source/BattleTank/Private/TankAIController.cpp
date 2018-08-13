// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));
	if (ATankAIController::GetAITank())
	{
		UE_LOG(LogTemp, Warning, TEXT("AI has possessed: %s"), *(GetAITank()->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No AI tank found..."));
	}
}

ATank* ATankAIController::GetAITank() const
{
	return Cast<ATank>(GetPawn());
}


