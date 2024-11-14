#include "Characters/OxnAnimInstance.h"
#include "Characters/CharacterBase.h"
#include "Characters/OxnCharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UOxnAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if ((OwningCharacter = Cast<ACharacterBase>(GetOwningActor())))
	{
		OwningCharacter->MovementModeChangedDelegate.AddUniqueDynamic(this, &UOxnAnimInstance::OnMovementModeChanged);
		CharacterMovementComponent = Cast<UOxnCharacterMovementComponent>(OwningCharacter->GetMovementComponent());
	}
}

void UOxnAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!OwningCharacter || !CharacterMovementComponent) return;

	if (!AnimData.bIsWalking) return;

	const auto Velocity = OwningCharacter->GetVelocity();
	AnimData.Speed = Velocity.SizeSquared() / FMath::Square(CharacterMovementComponent->GetMaxSpeed()) * 100.f;
	
	const auto Rotation = OwningCharacter->GetActorRotation();
	const auto Up = UKismetMathLibrary::GetUpVector(Rotation);
	const auto Forward = UKismetMathLibrary::GetForwardVector(Rotation);
	const FVector VelocityXYNormalized = CharacterMovementComponent->GetVelocityXY().GetSafeNormal(UE_SMALL_NUMBER, Forward);
	const auto Sign = FMath::Sign<float>(FVector::DotProduct(Up, FVector::CrossProduct(Forward, VelocityXYNormalized)));
	const auto Degrees = UKismetMathLibrary::RadiansToDegrees(FMath::Acos(FVector::DotProduct(Forward, VelocityXYNormalized)));
	AnimData.Direction = Sign * Degrees;
}

void UOxnAnimInstance::OnMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	const auto MovementMode = CharacterMovementComponent->MovementMode;
	
	if (MovementMode == MOVE_Falling)
		AnimData.bIsVelUp = Character->GetVelocity().Z > 0;

	AnimData.SetMovementMode(MovementMode);
}