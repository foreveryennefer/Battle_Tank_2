// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* TrackLeftToSet, UTankTrack* TrackRightToSet)
{
	TrackRight = TrackRightToSet;
	TrackLeft = TrackLeftToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we are replacing functionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto TankForwardMovementComponent = FVector::DotProduct(TankForward, AIForwardIntention);
	auto TankTurnComponent = FVector::CrossProduct(TankForward, AIForwardIntention);
	IntendMoveForward(TankForwardMovementComponent);
	IntendTurnRight(TankTurnComponent.Z);
}

void UTankMovementComponent::IntendMoveForward(float Throw) 
{
	if (!TrackLeft || !TrackRight) { return; }
	TrackRight->SetThrottle(Throw);
	TrackLeft->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!TrackLeft || !TrackRight) { return; }
	TrackRight->SetThrottle(-Throw);
	TrackLeft->SetThrottle(Throw);
}



