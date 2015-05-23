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
	Cast<UBoxComponent>(Trigger)->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	Trigger->AttachTo(this);
	Trigger->SetCollisionProfileName(FName("UI"));

	Trigger->OnClicked.AddDynamic(this, &UInteractiveComponent::OnClicked);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &UInteractiveComponent::OnBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &UInteractiveComponent::OnEndOverlap);
}


// Called when the game starts
void UInteractiveComponent::InitializeComponent()
{
	Super::InitializeComponent();
}


// Called every frame
void UInteractiveComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UInteractiveComponent::OnBeginOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASeasonsCharacter* player = Cast<ASeasonsCharacter>(Other);
	if (player)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("OnBeginOverlap")));
		CanPerformAction = true;

		// Notify blueprint related event handlers
		if (OnBeginOverlapDelegate.IsBound())
		{
			OnBeginOverlapDelegate.Broadcast(Other);
		}
	}
}

void UInteractiveComponent::OnEndOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ASeasonsCharacter* player = Cast<ASeasonsCharacter>(Other);
	if (player)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("OnEndOverlap")));
		CanPerformAction = false;

		// Notify blueprint related event handlers
		if (OnEndOverlapDelegate.IsBound())
		{
			OnEndOverlapDelegate.Broadcast(Other);
		}
	}
}

void UInteractiveComponent::OnClicked(UPrimitiveComponent* TouchedComponent)
{
	if (CanPerformAction)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("OnPerformAction")));

		// Notify blueprint related event handlers
		if (OnPerformAction.IsBound())
		{
			OnPerformAction.Broadcast(TouchedComponent);
		}
	}
}