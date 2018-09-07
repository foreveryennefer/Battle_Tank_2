// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* TrackLeftToSet, UTankTrack* TrackRightToSet)
{
	if (!TrackLeftToSet || !TrackRightToSet){ return; }
	TrackRight = TrackRightToSet;
	TrackLeft = TrackLeftToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) 
{
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);
	TrackRight->SetThrottle(Throw);
	TrackLeft->SetThrottle(Throw);

	//TODO prevent double speed due to dual-control use
}



