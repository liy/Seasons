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

	Trigger = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Cast<UBoxComponent>(Trigger)->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	Trigger->AttachTo(RootComponent);
	Trigger->SetCollisionProfileName(FName("UI"));

	Trigger->OnClicked.AddDynamic(this, &AInteractiveActor::OnPerformAction);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveActor::OnBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AInteractiveActor::OnEndOverlap);
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

void AInteractiveActor::OnBeginOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASeasonsCharacter* player = Cast<ASeasonsCharacter>(Other);
	if (player)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("OnBeginOverlap")));
		CanPerformAction = true;

		ReceiveOnBeginOverlap(Other, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}

void AInteractiveActor::OnEndOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ASeasonsCharacter* player = Cast<ASeasonsCharacter>(Other);
	if (player)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("OnEndOverlap")));
		CanPerformAction = false;

		ReceiveOnEndOverlap(Other, OtherComp, OtherBodyIndex);
	}
}

void AInteractiveActor::OnPerformAction(UPrimitiveComponent* TouchedComponent)
{
	if (CanPerformAction)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("OnPerformAction")));
		ReceiveOnPerformAction(TouchedComponent);
	}
}