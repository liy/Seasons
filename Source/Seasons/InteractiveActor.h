// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractiveActor.generated.h"

UCLASS()
class SEASONS_API AInteractiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	UShapeComponent* Trigger;

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction", meta = (FriendlyName = "OnPerformAction"))
	void ReceiveOnPerformAction(UPrimitiveComponent* TouchedComponent);
	// Have to add UFUNCTION() to make sure addDynamic() delegate work
	UFUNCTION()
	virtual void OnPerformAction(UPrimitiveComponent* TouchedComponent);

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction", meta = (FriendlyName = "OnBeginOverlap"))
	void ReceiveOnBeginOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Have to add UFUNCTION() to make sure addDynamic() delegate work
	UFUNCTION()
	virtual void OnBeginOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction", meta = (FriendlyName = "OnEndOverlap"))
	void ReceiveOnEndOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// Have to add UFUNCTION() to make sure addDynamic() delegate work
	UFUNCTION()
	virtual void OnEndOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	bool CanPerformAction;
};
