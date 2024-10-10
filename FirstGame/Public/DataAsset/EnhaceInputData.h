// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnhaceInputData.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class FIRSTGAME_API UEnhaceInputData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Enhance Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Enhance Input")
	UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Enhance Input")
	UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Enhance Input")
	UInputAction* IA_Attack;
	
	UPROPERTY(EditDefaultsOnly, Category = "Enhance Input")
	UInputAction* IA_SuperAttack;

};
