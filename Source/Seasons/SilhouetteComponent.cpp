// Fill out your copyright notice in the Description page of Project Settings.

#include "Seasons.h"
#include "SilhouetteComponent.h"
#include "Engine.h"
#include "InteractiveActor.h"


// Sets default values for this component's properties
USilhouetteComponent::USilhouetteComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void USilhouetteComponent::InitializeComponent()
{
	Super::InitializeComponent();

	InteractiveActor = Cast<AInteractiveActor>(GetOwner());
	if (InteractiveActor){
		InteractiveActor->OnEnterTrigger.AddUniqueDynamic(this, &USilhouetteComponent::OnEnterTrigger);
		InteractiveActor->OnLeaveTrigger.AddUniqueDynamic(this, &USilhouetteComponent::OnLeaveTrigger);
		InteractiveActor->GetTrigger()->OnBeginCursorOver.AddUniqueDynamic(this, &USilhouetteComponent::OnBeginCursorOver);
		InteractiveActor->GetTrigger()->OnEndCursorOver.AddUniqueDynamic(this, &USilhouetteComponent::OnEndCursorOver);
	}
}


// Called every frame
void USilhouetteComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void USilhouetteComponent::Show()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("ShowOutline")));

	if (InteractiveActor){
		for (UMeshComponent* mesh : InteractiveActor->GetMeshes()){
			mesh->bRenderCustomDepth = true;
			mesh->MarkRenderStateDirty();
		}
	}
}

void USilhouetteComponent::Hide()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("HideOutline")));

	if (InteractiveActor){
		for (UMeshComponent* mesh : InteractiveActor->GetMeshes()){
			mesh->bRenderCustomDepth = false;
			mesh->MarkRenderStateDirty();
		}
	}
}

void USilhouetteComponent::OnEnterTrigger(UPrimitiveComponent* Component)
{
	bInTrigger = true;
	Show();
}

void USilhouetteComponent::OnLeaveTrigger(UPrimitiveComponent* Component)
{
	bInTrigger = false;
	Hide();
}

void USilhouetteComponent::OnBeginCursorOver(UPrimitiveComponent* Component)
{
	Show();
}

void USilhouetteComponent::OnEndCursorOver(UPrimitiveComponent* Component)
{
	if (!bInTrigger){
		Hide();
	}
}