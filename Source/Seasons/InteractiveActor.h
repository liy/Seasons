// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractiveActor.generated.h"


UCLASS()
class SEASONS_API AInteractiveActor : public AActor
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPerformActionDelegate, UPrimitiveComponent*, TouchedComponent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginOverlapDelegate, AActor*, Other);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndOverlapDelegate, AActor*, Other);

public:	
	// Sets default values for this actor's properties
	AInteractiveActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	class UShapeComponent* Trigger;

	UPROPERTY(BlueprintAssignable, Category = "Interaction", meta = (FriendlyName = "OnPerformAction"))
	FOnPerformActionDelegate OnPerformAction;

	UPROPERTY(BlueprintAssignable, Category = "Interaction", meta = (FriendlyName = "OnBeginOverlap"))
	FOnBeginOverlapDelegate OnBeginOverlapDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Interaction", meta = (FriendlyName = "OnEndOverlap"))
	FOnEndOverlapDelegate OnEndOverlapDelegate;

	// Have to add UFUNCTION() to make sure addDynamic() delegate work
	UFUNCTION()
	virtual void OnTriggerClicked(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	virtual void OnTriggerBeginOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnTriggerEndOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual UMeshComponent* GetMesh();

protected:
	bool CanPerformAction;
};
