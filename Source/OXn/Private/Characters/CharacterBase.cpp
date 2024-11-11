#include "Characters/CharacterBase.h"
#include "Components/HealthComponent.h"

ACharacterBase::ACharacterBase()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}
