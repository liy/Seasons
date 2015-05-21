// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "InteractiveComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPerformActionDelegate, UPrimitiveComponent*, TouchedComponent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SEASONS_API UInteractiveComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractiveComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	UBoxComponent* Trigger;

	UPROPERTY(BlueprintAssignable, Category = "Interaction", meta = (FriendlyName = "OnPerformAction"))
	FOnPerformActionDelegate OnPerformActionDelegate;
	// Have to add UFUNCTION() to make sure addDynamic() delegate work
	UFUNCTION()
	virtual void OnPerformAction(UPrimitiveComponent* TouchedComponent);

	// Have to add UFUNCTION() to make sure addDynamic() delegate work
	UFUNCTION()
	virtual void OnBeginOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Have to add UFUNCTION() to make sure addDynamic() delegate work
	UFUNCTION()
	virtual void OnEndOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	bool CanPerformAction;
};
