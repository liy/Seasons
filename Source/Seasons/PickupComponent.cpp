// Fill out your copyright notice in the Description page of Project Settings.

#include "Seasons.h"
#include "PickupComponent.h"
#include "InteractiveActor.h"
#include "SeasonsCharacter.h"
#include "Engine.h"

// Sets default values for this component's properties
UPickupComponent::UPickupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UPickupComponent::InitializeComponent()
{
	Super::InitializeComponent();

	InteractiveActor = Cast<AInteractiveActor>(GetOwner());
	if (InteractiveActor){
		InteractiveActor->OnFireTrigger.AddUniqueDynamic(this, &UPickupComponent::OnPickup);
	}
}

// Called every frame
void UPickupComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPickupComponent::OnPickup(UPrimitiveComponent* TouchedComponent)
{
	AInteractiveActor* actor = Cast<AInteractiveActor>(TouchedComponent->GetOwner());
	if (actor){
		// TODO: maybe player controller to broadcast would be more suitable?
		// Make Character broadcast the OnPickup events
		ASeasonsCharacter* player = Cast<ASeasonsCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		if (player && player->OnPickup.IsBound()){
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("OnPickup C++")));
			player->OnPickup.Broadcast(this);
		}
	}
}