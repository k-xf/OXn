#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

using FOnValueChanged = TMulticastDelegate<void(float OldHealth, float NewHealth)>;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OXN_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	mutable FOnValueChanged OnHealthChanged;
	mutable FOnValueChanged OnMaxHealthChanged;

	UHealthComponent();
	
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE float GetHealthNormalized() const { return Health / MaxHealth; }

protected:
	void SetHealth(float NewHealth);
	void SetMaxHealth(float NewMaxHealth);

private:
	float Health{ 100.f };

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth{ 100.f };
};
