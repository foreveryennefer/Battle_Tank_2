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
	if (!GetControlledTank())
	{
		return;
	}

	FVector HitLocation; // OUT parameter
	if (GetSightRayHitLocation(HitLocation)){
		
		/*UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString())*/
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	/// Get the screen location of the crosshair
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(
		ViewportSizeX,
		ViewportSizeY
	);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXComponent, ViewportSizeY * CrosshairYComponent);
	
	FVector CameraWorldLocation;
	FVector CameraWorldDirection;

	bool GetCameraOritentation = DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		CameraWorldDirection
	);

	if (GetCameraOritentation)
	{
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *CameraWorldDirection.ToString());
	}

	return true;
}
