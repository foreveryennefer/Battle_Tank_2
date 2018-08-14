// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private: 
	ATank* GetControlledTank() const;
	void AimTowardsCrosshair(); //Start the tank moving the barrel so that a shot would hit where the crosshair interescts the world
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrosshairXComponent = 0.5;
	UPROPERTY(EditAnywhere)
		float CrosshairYComponent = 0.3333333;
};
