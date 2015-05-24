// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PickupType.h"
#include "PickupComponent.generated.h"

/**
 * 
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_PickUp")
	class UTexture2D* Texture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "_Pickup")
	EPickupType PickupType;

protected:
	class AInteractiveActor* InteractiveActor;

	// Make sure the listener function is marked as UFUNCTION
	UFUNCTION()
	void OnPickup(class UPrimitiveComponent* TouchedComponent);
};
