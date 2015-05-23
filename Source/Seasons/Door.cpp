// Fill out your copyright notice in the Description page of Project Settings.

#include "Seasons.h"
#include "Door.h"
#include "Engine.h"


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bClosed = true;
	bIsLocked = false;
	bAutoClose = false;
	bAutoOpen = false;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	Timeline = FTimeline();
	// Just in case the curve is not supplied
	if (Curve){
		FOnTimelineFloat onTimelineFunc{};
		onTimelineFunc.BindUFunction(this, "OnTimelineUpdate");
		// Curve is dynamically assigned, so timeline has to be initialized in BeginPlay()
		Timeline.AddInterpFloat(Curve, onTimelineFunc, FName("DoorTimeline"));
	}

	if (!bClosed) {
		Open(true);
	}
}

// Called every frame
void ADoor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (Timeline.IsPlaying()) {
		Timeline.TickTimeline(DeltaTime);
	}
}

void ADoor::OnTimelineUpdate_Implementation(float Value)
{
	//SetActorRelativeRotation(FRotator(0.f, Value, 0.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, Value, 0.f));
}

void ADoor::Open(bool useTransition = true)
{
	if (bIsLocked) {
		return;
	}

	if (useTransition) {
		Timeline.Play();
	}
	else{
		Timeline.SetNewTime(Timeline.GetTimelineLength());
	}

	bClosed = false;
}

void ADoor::Close(bool useTransition = true)
{
	if (useTransition) {
		Timeline.Reverse();
	}
	else{
		Timeline.SetNewTime(0.f);
	}
	bClosed = true;
}

void ADoor::ToggleDoor(bool useTransition = true)
{
	if (bClosed) {
		Open(useTransition);
	}
	else {
		Close(useTransition);
	}
}

void ADoor::OnTriggerClicked(UPrimitiveComponent* TouchedComponent)
{
	Super::OnTriggerClicked(TouchedComponent);

	if (CanFireTrigger) {
		ToggleDoor();
	}
}

void ADoor::OnTriggerBeginOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnTriggerBeginOverlap(Other, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (bAutoOpen) {
		Open();
	}
}

void ADoor::OnTriggerEndOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnTriggerEndOverlap(Other, OtherComp, OtherBodyIndex);

	if (bAutoClose) {
		Close();
	}
}