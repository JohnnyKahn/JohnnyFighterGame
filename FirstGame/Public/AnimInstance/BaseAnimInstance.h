// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class FIRSTGAME_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bShouldMove = false;
	
	UPROPERTY(BlueprintReadOnly)
	double StrafingValue = 0.0;

private:
	UPROPERTY()
	ACharacter* Character;
	UPROPERTY()
	UCharacterMovementComponent* MovementComponent;

	float GroundSpeed = 0.0f;

};
