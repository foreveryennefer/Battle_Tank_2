// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Turn(float RelativeSpeed)
{
	// Bound the speed
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	auto TurnChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewTurn = RelativeRotation.Yaw + TurnChange;
	SetRelativeRotation(FRotator(0, RawNewTurn, 0));
	/*UE_LOG(LogTemp, Warning, TEXT("Relative Rotation Pitch: %f"), RawNewTurn);*/
}


