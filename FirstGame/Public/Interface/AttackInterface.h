

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackInterface.generated.h"

class UAnimMontage;

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UAttackInterface : public UInterface
{
	GENERATED_BODY()
};

class FIRSTGAME_API IAttackInterface
{
	GENERATED_BODY()

public:
	virtual void I_PlayAnimMontage(UAnimMontage* AttackMontage) = 0;
	virtual void I_PlayStartAttackSound() = 0;
	virtual void I_EndAttack_AN() = 0;
	virtual void I_Combo_AN() = 0;
	virtual void I_TraceHit_ANS() = 0;
	virtual void I_BeginTraceHit_ANS() = 0;
	virtual FVector I_GetSocketLocation(const FName& SocketName) const  = 0;
	virtual void I_EnterCombat(float NewPercentHealthBoss);
	
	virtual void I_HitTarget(float NewPercentTarget);

	UFUNCTION(BlueprintCallable)
	virtual void I_RequestAttack() = 0;

	virtual void I_EndHitReact_AN() = 0;

	virtual void I_HandleAttackSuccess() = 0; // tru stamina

	virtual void I_HandleTargetDestroyed();

	virtual bool I_HasEnoughStamina(float CostStamina) const;

	virtual void I_StaminaUpdate();

	virtual bool I_IsAttacking() const = 0;

	virtual void I_RequestAttackFail_Health(float Health);


};
