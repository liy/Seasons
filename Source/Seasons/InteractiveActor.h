// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PickupType.h"
#include "InteractiveActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFireTriggerDelegate, UPrimitiveComponent*, TouchedComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnterTriggerDelegate, UPrimitiveComponent*, Component);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeaveTriggerDelegate, UPrimitiveComponent*, Component);

UCLASS()
class SEASONS_API AInteractiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	class USceneComponent* MeshContainer;

	UPROPERTY(BlueprintAssignable, Category = "Interaction", meta = (DisplayName = "OnFireTrigger"))
	FOnFireTriggerDelegate OnFireTrigger;

	UPROPERTY(BlueprintAssignable, Category = "Interaction", meta = (DisplayName = "OnEnterTrigger"))
	FOnEnterTriggerDelegate OnEnterTrigger;

	UPROPERTY(BlueprintAssignable, Category = "Interaction", meta = (DisplayName = "OnLeaveTrigger"))
	FOnLeaveTriggerDelegate OnLeaveTrigger;

	// Can be implemented in blueprint, but this function is not exposed to other blueprint. A separated BlueprintCallable
	// function is defined in C++ for exposing to global blueprints.
	UFUNCTION(BlueprintImplementableEvent, Category = "Pickup", meta = (DisplayName = "OnInteract"))
	bool OnInteract(EPickupType pickupType);

	// This function expose the ability OnInteract function to global blueprint. It simply calls OnInteract function.
	// But, you can always override it in C++ sub class.
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	virtual bool InteractWith(EPickupType pickupType);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	class ASeasonsPlayerController* GetController() const;

	TArray<class UMeshComponent*> GetMeshes() const;

	class UShapeComponent* GetTrigger() const;

protected:
	bool CanFireTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	class UShapeComponent* Trigger;

	UFUNCTION()
	virtual void OnTriggerClicked(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	virtual void OnTriggerBeginOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnTriggerEndOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
