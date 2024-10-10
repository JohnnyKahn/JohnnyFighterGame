

#include "Component/HealthComponent.h"
#include "DataAsset/BaseCharacterData.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UHealthComponent::SetupHealthComponent(UBaseCharacterData* BCD)
{
	if (BCD) 
	{
		Health = BCD->Health;
		MaxHealth = BCD->MaxHealth;
	}
}

void UHealthComponent::UpdateHealthByDame(float Dame)
{
	Health = FMath::Max(Health - Dame, 0.0f);
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

