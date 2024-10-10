
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"

class UBaseCharacterData;
class IAttackInterface;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTGAME_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStaminaComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupStaminaComponent(UBaseCharacterData* BCD);
	void UpdateStamina(float Cost);

protected:
	virtual void BeginPlay() override;

public:	

	float Stamina = 100.0f;
	float MaxStamina = 100.0f;
	float RegenSpeed = 0.0f;

private:

	UPROPERTY()
	TScriptInterface<IAttackInterface> AttackInterface;
	
};
