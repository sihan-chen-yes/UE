// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Moving")
	FVector PlatformVelocity = FVector(100, 0, 0);
	
	UPROPERTY(EditAnywhere, Category = "Moving")
	float MaxDistance = 100;
	
	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator RotationVelocity = FRotator::ZeroRotator;
	
	UPROPERTY(EditAnywhere, Category = "Rotation")
	bool ReverseSwitch = false;
	
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float MaxRotation = 180.0f;

	FVector StartLocation = FVector::ZeroVector;
	
	FRotator StartRotation = FRotator::ZeroRotator;

	float TotalYawRotation = 0.0f;

	void MovePlatform(float DeltaTime);
	
	void RotatePlatform(float DeltaTime);

	bool ShouldPlatformReturn(FVector CurrentLocation) const;

	float GetMovedDistance(FVector CurrentLocation) const;

	bool ShouldPlatformReverse(FRotator CurrentRotation) const;
};
