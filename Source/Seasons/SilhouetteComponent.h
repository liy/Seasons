// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SilhouetteComponent.generated.h"

// TODO: Extends UActorComponent instead.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SEASONS_API USilhouetteComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USilhouetteComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

protected:
	// Have to add UFUNCTION() to make sure addDynamic() delegate work
	UFUNCTION()
	void OnEnterTrigger(UPrimitiveComponent* Component);

	UFUNCTION()
	void OnLeaveTrigger(UPrimitiveComponent* Component);

	UFUNCTION()
	void OnBeginCursorOver(UPrimitiveComponent* Component);

	UFUNCTION()
	void OnEndCursorOver(UPrimitiveComponent* Component);

	// Show silhouette
	void Show();

	// Hide silhouette
	void Hide();

	class AInteractiveActor* GetInteractiveOwner() const;

	class AInteractiveActor* InteractiveActor;

private:
	// Whether the actor is still in the trigger volume
	bool bInTrigger;
};
