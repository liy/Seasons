// Fill out your copyright notice in the Description page of Project Settings.

#include "Seasons.h"
#include "Door.h"
#include "Engine.h"


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bFlipflop = true;
	bIsLocked = false;
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
}

// Called every frame
void ADoor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (Timeline.IsPlaying())
	{
		Timeline.TickTimeline(DeltaTime);
	}
}

void ADoor::OnTimelineUpdate_Implementation(float Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("OnTimelineUpdate: timeline: %f  value:%f"), Timeline.GetPlaybackPosition(), Value));
	SetActorRelativeRotation(FRotator(0.f, Value, 0.f));
}

void ADoor::ToggleDoor()
{
	if (bFlipflop)
	{
		if (bIsLocked)
		{
			return;
		}

		Timeline.Play();
	}
	else
	{
		Timeline.Reverse();
	}
	bFlipflop = !bFlipflop;
}