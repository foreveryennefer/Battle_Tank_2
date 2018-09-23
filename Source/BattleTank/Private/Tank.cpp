// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "../Public/Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Black_Cat: Tank CPP Construct"), *TankName)
}

void ATank::BeginPlay()
{
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Black_Cat: Tank CPP BeginPlay"), *TankName)
	Super::BeginPlay(); // Needed for BP begin-play to run
}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Aiming Component found!"));
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (!Barrel) { return; }
	if (Barrel && isReloaded) {
		UE_LOG(LogTemp, Warning, TEXT("Tank is firing!"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			Barrel->GetSocketLocation(FName(TEXT("Projectile"))),
			Barrel->GetSocketRotation(FName(TEXT("Projectile")))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
	
}

