// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
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

	UPROPERTY(BlueprintAssignable, Category = "Interaction", meta = (FriendlyName = "OnFireTrigger"))
	FOnFireTriggerDelegate OnFireTrigger;

	UPROPERTY(BlueprintAssignable, Category = "Interaction", meta = (FriendlyName = "OnEnterTrigger"))
	FOnEnterTriggerDelegate OnEnterTrigger;

	UPROPERTY(BlueprintAssignable, Category = "Interaction", meta = (FriendlyName = "OnLeaveTrigger"))
	FOnLeaveTriggerDelegate OnLeaveTrigger;

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
