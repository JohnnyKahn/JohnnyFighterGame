
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UBaseCharacterData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();
	void SetupHealthComponent(UBaseCharacterData* BCD);
	void UpdateHealthByDame(float Dame);

protected:
	virtual void BeginPlay() override;

public:
	float Health = 100.0f;
	float MaxHealth = 100.0f;
		
};
