// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Seasons.h"
#include "SeasonsCharacter.h"
#include "InteractiveActor.h"

ASeasonsCharacter::ASeasonsCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Camera rotation related.
	RotationSpeed = 6.f;
	TargetYaw = -45.f;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 3000.f;
	CameraBoom->RelativeRotation = FRotator(-45.f, TargetYaw, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	TopDownCameraComponent->FieldOfView = 60.f;

	// Allow smooth rotation
	PrimaryActorTick.bCanEverTick = true;
}

void ASeasonsCharacter::Tick(float delta)
{
	Super::Tick(delta);

	const FRotator currentRotator = CameraBoom->GetComponentRotation();
	FRotator targetRotator = FRotator(currentRotator.Pitch, TargetYaw, currentRotator.Roll);
	// Only do interpolation when difference it big enough 
	if (abs(currentRotator.Yaw - TargetYaw) >= 0.05f){
		// Smooth interpolate the rotation
		targetRotator = FMath::RInterpTo(currentRotator, targetRotator, delta, RotationSpeed);
	}
	CameraBoom->SetRelativeRotation(targetRotator);
}

void ASeasonsCharacter::CameraRotateLeft()
{
	TargetYaw += 90.f;
}

void ASeasonsCharacter::CameraRotateRight()
{
	TargetYaw -= 90.f;
}