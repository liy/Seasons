// Fill out your copyright notice in the Description page of Project Settings.

#include "Seasons.h"
#include "InteractiveActor.h"
#include "SeasonsCharacter.h"
#include "Engine.h"

// Sets default values
AInteractiveActor::AInteractiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);

	Trigger = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Cast<UBoxComponent>(Trigger)->SetBoxExtent(FVector(80.f, 110.f, 60.f));
	Trigger->SetCollisionProfileName(FName("UI"));
	Trigger->AttachTo(RootComponent);

	Trigger->OnClicked.AddDynamic(this, &AInteractiveActor::OnTriggerClicked);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveActor::OnTriggerBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AInteractiveActor::OnTriggerEndOverlap);
}

// Called when the game starts or when spawned
void AInteractiveActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AInteractiveActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AInteractiveActor::OnTriggerBeginOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void AInteractiveActor::OnTriggerEndOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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

void AInteractiveActor::OnTriggerClicked(UPrimitiveComponent* TouchedComponent)
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