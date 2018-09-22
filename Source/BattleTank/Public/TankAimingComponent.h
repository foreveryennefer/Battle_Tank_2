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
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetBarrelReference(UTankBarrel * BarrelToSet);
	void SetTurretReference(UTankTurret * TurretToSet);
	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);

protected:
	UPROPERTY(BluePrintReadOnly, Category = "Input")
		EFiringStatus FiringStatus = EFiringStatus::Aiming;

private:
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;
	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);

};
