#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "OxnCharacterMovementComponent.generated.h"

UCLASS()
class OXN_API UOxnCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	FVector GetVelocityXY() const;
	float GetHorizontalSpeed(float Scale = 100.f) const;
};
