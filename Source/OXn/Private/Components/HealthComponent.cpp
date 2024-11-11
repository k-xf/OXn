#include "Components/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::SetHealth(const float NewHealth)
{
	const auto OldHealth = Health;
	Health = FMath::Clamp(NewHealth, 0.f, GetMaxHealth());
	OnHealthChanged.Broadcast(OldHealth, Health);
}

void UHealthComponent::SetMaxHealth(const float NewMaxHealth)
{
	const auto OldMaxHealth = MaxHealth;
	MaxHealth = NewMaxHealth;
	OnHealthChanged.Broadcast(OldMaxHealth, MaxHealth);

}