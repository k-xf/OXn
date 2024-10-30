#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "OxnAnimInstance.generated.h"

class AOxnCharacter;
class UOxnCharacterMovementComponent;
enum class ECharacterState : uint8;

UCLASS()
class OXN_API UOxnAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AOxnCharacter> Character;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UOxnCharacterMovementComponent> CharacterMovementComponent;

	UPROPERTY(BlueprintReadOnly)
	float Speed;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsMoving;
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
};
