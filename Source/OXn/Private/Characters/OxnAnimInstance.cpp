#include "Characters/OxnAnimInstance.h"
#include "Characters/OxnCharacter.h"
#include "Characters/OxnCharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UOxnAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if ((Character = Cast<AOxnCharacter>(GetOwningActor())))
		CharacterMovementComponent = Cast<UOxnCharacterMovementComponent>(Character->GetMovementComponent());
}

void UOxnAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!CharacterMovementComponent) return;
	
	Speed = CharacterMovementComponent->GetHorizontalSpeed();
	bIsMoving = Speed > 0.f;
}

void UOxnAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	
}