// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "../Public/TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 

	// ...
}

void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (RoundsLeft <= 0)
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

void UTankAimingComponent::Initialise(UTankBarrel* TankBarrelToSet, UTankTurret* TankTurretToSet) {
	Barrel = TankBarrelToSet;
	Turret = TankTurretToSet;
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim) 
{
	if (!ensure(Barrel)) {
		UE_LOG(LogTemp, Warning, TEXT("No barrel found!"))
		return;
	}
	
	FVector OutLaunchVelocity = FVector(0.f, 0.f, 0.f);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		WorldSpaceAim,

		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
		/*UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());*/
		auto Time = GetWorld()->GetTimeSeconds();
		/*UE_LOG(LogTemp, Warning, TEXT("%f: New aiming solution found"), Time);*/
	}
	else {
		auto Time = GetWorld()->GetTimeSeconds();
		/*UE_LOG(LogTemp, Warning, TEXT("%f: No aiming solution found"), Time);*/
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
	// Get the rotation of the player's aim relative to the default
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	// Rotate the barrel socket as per the player's aim as a tick-component

	if (!ensure(Barrel)) { return; }
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	// Get the rotation of the player's aim relative to the default
	auto BarrelRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	if (!ensure(Turret)) { return; }
	/// Always find the shortest rotation possible
	if (DeltaRotator.Yaw > 180)
	{
		Turret->Turn(-(360-DeltaRotator.Yaw));
		UE_LOG(LogTemp, Warning, TEXT("Standard: %f"), DeltaRotator.Yaw)
	}
	else if (DeltaRotator.Yaw < -180)
	{
		Turret->Turn(-(DeltaRotator.Yaw - 360));
		UE_LOG(LogTemp, Warning, TEXT("Turning the other way: %f"), DeltaRotator.Yaw)
	}
	else
	{
		Turret->Turn(DeltaRotator.Yaw);
		UE_LOG(LogTemp, Warning, TEXT("Standard turn: %f"), DeltaRotator.Yaw)
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto ForwardVector = Barrel->GetForwardVector();
	return !ForwardVector.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::Fire()
{
	
	
	if (FiringStatus != EFiringStatus::Reloading) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBluePrint)) { return; }
		UE_LOG(LogTemp, Warning, TEXT("Tank is firing!"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			Barrel->GetSocketLocation(FName(TEXT("Projectile"))),
			Barrel->GetSocketRotation(FName(TEXT("Projectile")))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}

	if (GetRoundsLeft() != 0)
	{
		RoundsLeft -= 1;
	}
}



