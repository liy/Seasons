// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractiveActor.h"
#include "Components/TimelineComponent.h"
#include "Door.generated.h"

/*
 * Generic Door class
 */
UCLASS()
class SEASONS_API ADoor : public AInteractiveActor
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	bool bAutoClose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	bool bAutoOpen;

	// Door openning and closing timeline update
	UFUNCTION(BlueprintNativeEvent, Category = "Door")
	void OnTimelineUpdate(float Value);
	virtual void OnTimelineUpdate_Implementation(float Value);

	void Open(bool useTransition);

	void Close(bool useTransition);

	void ToggleDoor(bool useTransition);

protected:
	UPROPERTY(EditInstanceOnly, Category = "Door", DisplayName = "Timeline Curve")
	UCurveFloat* Curve;

	virtual void OnTriggerClicked(UPrimitiveComponent* TouchedComponent) override;

	// For auto enter feature
	virtual void OnTriggerBeginOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	// For auto close feature
	virtual void OnTriggerEndOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

private:
	FTimeline Timeline;

	void TickTimeline();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (AllowPrivateAccess = "true"))
	bool bClosed;
};
