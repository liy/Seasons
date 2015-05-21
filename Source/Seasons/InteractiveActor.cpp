// Fill out your copyright notice in the Description page of Project Settings.

#include "Seasons.h"
#include "InteractiveActor.h"
#include "Engine.h"


// Sets default values
AInteractiveActor::AInteractiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);


	//Mesh->OnClicked.AddDynamic(this, &AInteractiveActor::Onclick);
	OnClicked.AddDynamic(this, &AInteractiveActor::ClickHandler);
}

// Called when the game starts or when spawned
void AInteractiveActor::BeginPlay()
{
	Super::BeginPlay();

	EnableInput(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void AInteractiveActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AInteractiveActor::ClickHandler()
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("ClickHandler")));
}