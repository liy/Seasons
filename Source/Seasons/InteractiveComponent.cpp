// Fill out your copyright notice in the Description page of Project Settings.

#include "Seasons.h"
#include "InteractiveComponent.h"
#include "Engine.h"
#include "SeasonsCharacter.h"


// Sets default values for this component's properties
UInteractiveComponent::UInteractiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	//Trigger = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &UInteractiveComponent::OnBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &UInteractiveComponent::OnEndOverlap);
	Trigger->AttachTo(this);
}


// Called when the game starts
void UInteractiveComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// ...
	
}


// Called every frame
void UInteractiveComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UInteractiveComponent::OnBeginOverlap_Implementation(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("OnBeginOverlap")));

	ASeasonsCharacter* player = Cast<ASeasonsCharacter>(Other);
	if (player)
	{
		CanPerformAction = true;
	}
}

void UInteractiveComponent::OnEndOverlap_Implementation(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("OnEndOverlap")));

	ASeasonsCharacter* player = Cast<ASeasonsCharacter>(Other);
	if (player)
	{
		CanPerformAction = false;
	}
}

void UInteractiveComponent::OnPerformAction_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("OnPerformAction")));
}