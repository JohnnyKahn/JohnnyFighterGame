// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/BaseCharacterData.h"

UBaseCharacterData::UBaseCharacterData()
{
	CostMap.Emplace(EAttackType::Normal, 20.0f);
	CostMap.Emplace(EAttackType::Super, 20.0f);

	DameMap.Emplace(EAttackType::Normal, 20.0f);
	DameMap.Emplace(EAttackType::Super, 20.0f);
}
