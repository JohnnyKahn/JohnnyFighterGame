// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAttack_AN.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTGAME_API UEndAttack_AN : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(
		USkeletalMeshComponent* MeshComp, 
		UAnimSequenceBase* Animation, 
		const FAnimNotifyEventReference& EventReference) override;
	
};
