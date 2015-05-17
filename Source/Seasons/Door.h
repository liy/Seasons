// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Door.generated.h"

UCLASS()
class SEASONS_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Whehter the door is locked, if it is locked, it cannot be opened.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	bool bIsLocked;

	UFUNCTION(BlueprintCallable, Category = "Door")
	void ToggleDoor();

	UFUNCTION(BlueprintNativeEvent, Category = "Door")
	void OnTimelineUpdate(float Value);
	void OnTimelineUpdate_Implementation(float Value);

protected:

	UPROPERTY(EditInstanceOnly, Category = "Door", DisplayName = "Timeline Curve")
	UCurveFloat* Curve;


private:
	FTimeline Timeline;

	void TickTimeline();

	bool bFlipflop;

	
};
