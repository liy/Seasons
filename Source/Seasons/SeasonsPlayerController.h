// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "PickupType.h"
#include "SeasonsPlayerController.generated.h"

UCLASS()
class ASeasonsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASeasonsPlayerController(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetSelectedPickup(EPickupType type);

	UFUNCTION(BlueprintCallable, Category="Pickup")
	EPickupType GetSelectedPickup();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Indicate the selecte pickup
	EPickupType SelectedPickupType;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	void CameraRotateLeft();
	void CameraRotateRight();
};


