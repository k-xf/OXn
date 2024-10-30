#include "Characters/OxnCharacterMovementComponent.h"

FVector UOxnCharacterMovementComponent::GetVelocityXY() const
{
	const auto Rot = GetLastUpdateRotation();
	const auto UpVector = FRotationMatrix(Rot).GetScaledAxis(EAxis::Z);
	return Velocity - UpVector * FVector::DotProduct(UpVector, Velocity);
}