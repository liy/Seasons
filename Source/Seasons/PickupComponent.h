// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PickupType.h"
#include "PickupComponent.generated.h"

/**
 * Handle the pickup triggering, and providing pick information, e.g. pick type.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SEASONS_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UPickupComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	class UTexture2D* Texture;

	// The type of the the pickup
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	EPickupType Type;

protected:
	class AInteractiveActor* InteractiveActor;

	// Bind to tirgger overlap event, and broadcast the OnPickup events
	// Make sure the listener function is marked as UFUNCTION
	UFUNCTION()
	void OnPickup(class UPrimitiveComponent* TouchedComponent);
};
