#include "Characters/OxnCharacterMovementComponent.h"

FVector UOxnCharacterMovementComponent::GetVelocityXY() const
{
	const auto Rot = GetLastUpdateRotation();
	const auto UpVector = FRotationMatrix(Rot).GetScaledAxis(EAxis::Z);
	return Velocity - UpVector * FVector::DotProduct(UpVector, Velocity);
}

float UOxnCharacterMovementComponent::GetHorizontalSpeed(const float Scale) const
{
	return GetVelocityXY().SizeSquared() / FMath::Pow(GetMaxSpeed(), 2.f) * Scale;
}
