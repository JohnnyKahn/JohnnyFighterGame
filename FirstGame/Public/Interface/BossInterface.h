// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BossInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBossInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FIRSTGAME_API IBossInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void I_HandleSeePlayer(AActor* PlayerActor) = 0;
	virtual FVector I_GetPatrolLocation() = 0;
	virtual void I_StopAttackAfterPlayerDead() = 0;

};
