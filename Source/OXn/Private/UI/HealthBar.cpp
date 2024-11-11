#include "UI/HealthBar.h"
#include "Characters/CharacterBase.h"
#include "Components/HealthComponent.h"
#include "Components/ProgressBar.h"

void UHealthBar::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (const auto* const Player = GetOwningPlayerPawn<ACharacterBase>())
		if ((HealthComponent = Player->GetHealthComponent()))
			HealthComponent->OnHealthChanged.AddUObject(this, &UHealthBar::UpdateBar);
}

void UHealthBar::UpdateBar(const float, const float)
{
	HealthBar->SetPercent(HealthComponent->GetHealthNormalized());
}
