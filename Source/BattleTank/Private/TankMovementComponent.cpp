// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* TrackLeftToSet, UTankTrack* TrackRightToSet)
{
	TrackRight = TrackRightToSet;
	TrackLeft = TrackLeftToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) 
{
	if (!TrackLeft || !TrackRight) { return; }
	TrackRight->SetThrottle(Throw);
	TrackLeft->SetThrottle(Throw);

	//TODO prevent double speed due to dual-control use
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!TrackLeft || !TrackRight) { return; }
	TrackRight->SetThrottle(-Throw);
	TrackLeft->SetThrottle(Throw);

	//TODO prevent double speed due to dual-control use
}



