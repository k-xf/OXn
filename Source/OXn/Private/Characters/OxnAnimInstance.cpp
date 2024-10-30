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

void UOxnAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!Character || !CharacterMovementComponent) return;
	
	Speed = CharacterMovementComponent->GetVelocityXY().SizeSquared() / FMath::Pow(CharacterMovementComponent->GetMaxSpeed(), 2.f) * 100.f;
	bIsMoving = Speed > 0.f;
}