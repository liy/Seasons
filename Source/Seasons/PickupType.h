#pragma once

#include "PickupType.generated.h"

UENUM(BlueprintType)
enum class EPickupType : uint8
{
	None,

	// Level 1
	Key,
	Apple,
	Walnut,
	Wood,
	Axe,
	Message,
	Letter,
	Ring
};

// Dummy, just make it compile correctly
UCLASS()
class UPickupType : public UObject
{
	GENERATED_BODY()
};