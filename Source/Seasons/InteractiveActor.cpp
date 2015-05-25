// Fill out your copyright notice in the Description page of Project Settings.

#include "Seasons.h"
#include "InteractiveActor.h"
#include "SeasonsCharacter.h"
#include "SeasonsPlayerController.h"
#include "Engine.h"

// Sets default values
AInteractiveActor::AInteractiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	MeshContainer = CreateDefaultSubobject<USceneComponent>(TEXT("RootMesh"));
	MeshContainer->AttachTo(RootComponent);

	Trigger = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Cast<UBoxComponent>(Trigger)->InitBoxExtent(FVector(80.f, 110.f, 60.f));
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
		CanFireTrigger = true;

		// Notify blueprint related event handlers
		if (OnEnterTrigger.IsBound())
		{
			OnEnterTrigger.Broadcast(OtherComp);
		}

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("OnTriggerBeginOverlap")));
	}
}

void AInteractiveActor::OnTriggerEndOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ASeasonsCharacter* player = Cast<ASeasonsCharacter>(Other);
	if (player)
	{
		CanFireTrigger = false;

		if (OnLeaveTrigger.IsBound())
		{
			OnLeaveTrigger.Broadcast(OtherComp);
		}

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("OnTriggerEndOverlap")));
	}
}

void AInteractiveActor::OnTriggerClicked(UPrimitiveComponent* TouchedComponent)
{
	if (CanFireTrigger)
	{
		if (OnFireTrigger.IsBound())
		{
			OnFireTrigger.Broadcast(TouchedComponent);
		}

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("OnTriggerClicked")));
	}
}

TArray<UMeshComponent*> AInteractiveActor::GetMeshes() const
{
	TArray<UActorComponent*> components = GetComponentsByClass(UMeshComponent::StaticClass());
	TArray<UMeshComponent*> meshes;
	for (UActorComponent* component : components){
		meshes.Add(Cast<UMeshComponent>(component));
	}
	return meshes;
}

UShapeComponent* AInteractiveActor::GetTrigger() const
{
	return Trigger;
}

ASeasonsPlayerController* AInteractiveActor::GetController() const
{
	return Cast<ASeasonsPlayerController>(GetWorld()->GetFirstPlayerController());
}