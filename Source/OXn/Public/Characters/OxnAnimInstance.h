#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "OxnAnimInstance.generated.h"

class ACharacterBase;
class UOxnCharacterMovementComponent;

/**
 * MovementMode for OxnAnimInstance, without sacrificing Fast Path Optimization 
 */
USTRUCT(BlueprintType)
struct FAnimData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	uint8 bIsWalking : 1{};

	UPROPERTY(BlueprintReadOnly)
	uint8 bIsJumping : 1{};
	
	UPROPERTY(BlueprintReadOnly)
	uint8 bIsFalling : 1{};

	UPROPERTY(BlueprintReadOnly)
	uint8 bIsSwimming : 1{};

	UPROPERTY(BlueprintReadOnly)
	uint8 bIsFlying : 1{};

	UPROPERTY(BlueprintReadOnly)
	uint8 bIsVelUp : 1{};

	UPROPERTY(BlueprintReadOnly)
	float Speed{};
	
	UPROPERTY(BlueprintReadOnly)
	float Direction{};
	
	void SetMovementMode(const EMovementMode MovementMode)
	{
		ResetMovementMode();
		
		switch (MovementMode)
		{
		case MOVE_Walking:
			bIsWalking = 1;
			break;
		case MOVE_Falling:
			bIsFalling = 1;
			break;
		case MOVE_Swimming:
			bIsSwimming = 1;
			break;
		case MOVE_Flying:
			bIsFlying = 1;
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("Unhandled MovementMode(OxnAnimInstance): %s"), *UEnum::GetValueAsString(MovementMode))
		}
	}
	
	void ResetMovementMode()
	{
		bIsWalking = 0;
		bIsFalling = 0;
		bIsSwimming = 0;
		bIsFlying = 0;
		bIsVelUp = 0;
	}
};

UCLASS()
class OXN_API UOxnAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	FAnimData AnimData;
	
    UPROPERTY(Transient, BlueprintReadOnly)
    TObjectPtr<ACharacterBase> OwningCharacter;
    	
    UPROPERTY(Transient, BlueprintReadOnly)
    TObjectPtr<UOxnCharacterMovementComponent> CharacterMovementComponent;
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION()
	virtual void OnMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);
};
