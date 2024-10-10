// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/AttackInterface.h"

// Add default functionality here for any IAttackInterface functions that are not pure virtual.

void IAttackInterface::I_EnterCombat(float NewPercent)
{
}

void IAttackInterface::I_HitTarget(float NewPercentTarget)
{
}

void IAttackInterface::I_HandleTargetDestroyed()
{
}

bool IAttackInterface::I_HasEnoughStamina(float CostStamina) const
{
    return false;
}

void IAttackInterface::I_StaminaUpdate()
{
}

void IAttackInterface::I_RequestAttackFail_Health(float Health)
{
}


