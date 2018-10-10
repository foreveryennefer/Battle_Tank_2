// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"
#include "Projectile.h"
#include "TankAimingComponent.generated.h" // Last include

// Enum for aiming-state
UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Reloading,
	Aiming,
	OutOfAmmo
};

// Forward Declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

// Hold barrel's properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BluePrintCallable, Category = "Setup")
		void Initialise(UTankBarrel* TankBarrelToSet, UTankTurret* TankTurretToSet);

	void AimAt(FVector WorldSpaceAim);

	UFUNCTION(BluePrintCallable, Category = "Firing")
		void Fire();

	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BluePrintCallable, Category = "Input")
		int32 GetRoundsLeft() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BluePrintReadOnly, Category = "Input")
		EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
	UTankAimingComponent();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;
	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);
	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000.0;

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBluePrint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
		int32 RoundsLeft = 3;

	// Used Dummy used to calcualte the IsReloaded value
	double LastFireTime = 0;

	FVector AimDirection;
};
