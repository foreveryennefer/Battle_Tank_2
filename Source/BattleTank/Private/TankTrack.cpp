// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
	//UE_LOG(LogTemp, Warning, TEXT("I'm hit"))
}

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("I'm hit!"))
	// Drive the tracks
	DriveTrack();
	
	//Apply sideways force
	ApplySidewayForce();

	CurrentThrottle = 0.f;
}

void UTankTrack::ApplySidewayForce()
{
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector()); //Float
	//UE_LOG(LogTemp, Warning, TEXT("Slippage Velocity of tank %s: %f"), *GetOwner()->GetName(), SlippageSpeed)
	//Work-out the required acceleration this frame to correct

	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	//Calculate and apply sideways for (F = ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //Two tracks
	TankRoot->AddForce(CorrectionForce);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetRightVector().ToString())
}

void UTankTrack::DriveTrack()
{
	// TODO clamp actual throttle value so player cannot over-drive
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	UE_LOG(LogTemp, Warning, TEXT("Force applied: %s"), *ForceApplied.ToString())
}

void UTankTrack::SetThrottle(float throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + throttle, -1, 1);
	//UE_LOG(LogTemp, Warning, TEXT("Throttle: %f"), CurrentThrottle)
}

