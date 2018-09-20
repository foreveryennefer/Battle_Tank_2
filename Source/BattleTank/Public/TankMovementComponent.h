// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendTurnRight(float Throw);
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MyVariable = 4545.f;

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankTrack* TrackLeftToSet, UTankTrack* TrackRightToSet);

	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 80000000.f; // Assume tank mass is 40 tonnes and 10 ms^-2

	// TODO check best protection of this method
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack* TrackLeft = nullptr;
	UTankTrack* TrackRight = nullptr;
};