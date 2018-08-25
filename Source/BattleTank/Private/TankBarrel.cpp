// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTank.h"

/// Elevate the barrel within a bounded speedlimit and height
void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Bound the speed
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	// Bound the Elevation
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto ElevationClamped = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(ElevationClamped, 0, 0));

	// UE_LOG(LogTemp, Warning, TEXT("Relative Rotation Pitch: %f"), RelativeRotation.Pitch); TESTING
}
