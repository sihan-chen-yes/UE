// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "GameFramework/Character.h"

// Sets default values
AMovingPlatform::AMovingPlatform() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay() {
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	StartRotation = GetActorRotation();

	FString ActorName = GetName();

	UE_LOG(LogTemp, Display, TEXT("Configuration, MovedDistance %f, Name:%s"), MaxDistance, *ActorName);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime) {
	FVector CurrentLocation = GetActorLocation();
	// calculate new location
	CurrentLocation += DeltaTime * PlatformVelocity;

	if (ShouldPlatformReturn(CurrentLocation)) {
		// if outside moving range
		// debug part
		float OverShoot = GetMovedDistance(CurrentLocation) - MaxDistance;
		FString ActorName = GetName();
		UE_LOG(LogTemp, Display, TEXT("Platform Overshoot:%f, Name:%s"), OverShoot, *ActorName);

		// get moving direction
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		// 1. update the start location at the end
		// 2. set current location at the end
		// 3. reverse the moving direction
		StartLocation += MoveDirection * MaxDistance;
		CurrentLocation = StartLocation;
		PlatformVelocity *= -1;
	}
	// set current location
	SetActorLocation(CurrentLocation);
}

void AMovingPlatform::RotatePlatform(float DeltaTime) {
	FQuat DeltaQuat = FQuat(FRotator(DeltaTime * RotationVelocity));

	// calculate new rotation
	FQuat CurrentRotation = GetActorQuat() * DeltaQuat;

	//Yaw may lt zero!
	TotalYawRotation += DeltaQuat.Rotator().Yaw;
	
	// set new rotation
	AddActorLocalRotation(DeltaQuat.Rotator());
	
	if (ReverseSwitch && ShouldPlatformReverse(CurrentRotation.Rotator())) {
		// 1. reverse the moving direction
		// 2.clear the accumulated yaw
		RotationVelocity *= -1;
		TotalYawRotation = 0.0f;
	}
}

bool AMovingPlatform::ShouldPlatformReturn(FVector CurrentLocation) const {
	return GetMovedDistance(CurrentLocation) > MaxDistance;
}

float AMovingPlatform::GetMovedDistance(FVector CurrentLocation) const {
	return FVector::Dist(StartLocation, CurrentLocation);
}

bool AMovingPlatform::ShouldPlatformReverse(FRotator CurrentRotation) const {
	// UE_LOG(LogTemp, Display, TEXT("Rotation Overshoot:%f"), FMath::Abs(TotalYawRotation));
	return FMath::Abs(TotalYawRotation) >= MaxRotation;
}