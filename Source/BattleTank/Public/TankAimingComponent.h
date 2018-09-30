// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h" // Last include

// Enum for aiming-state
UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Reloading,
	Aiming
};

// Forward Declaration
class UTankBarrel; 
class UTankTurret;

// Hold barrel's properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BluePrintCallable, Category = "Setup")
		void Initialise(UTankBarrel* TankBarrelToSet, UTankTurret* TankTurretToSet);

	void AimAt(FVector WorldSpaceAim);

protected:
	UPROPERTY(BluePrintReadOnly, Category = "Input")
		EFiringStatus FiringStatus = EFiringStatus::Locked;

private:
	UTankAimingComponent();
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;
	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000.0;
};
