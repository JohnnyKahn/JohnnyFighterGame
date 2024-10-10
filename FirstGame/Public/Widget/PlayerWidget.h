// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

class UProgressBar;

UCLASS()
class FIRSTGAME_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdataHealthBarPlayer(float NewPercent);
	void UpdataStaminaBarPlayer(float NewPercent);
	void UpdataHealthBarEnemy(float NewPercent);
	void HideEnemyStats();

private:	
	UPROPERTY(meta = (BindWidget)) //Them macro nay thi bien nay ung voi thanh mau trong BP
	UProgressBar* PlayerHealthBar;

	UPROPERTY(meta = (BindWidget)) //Them macro nay thi bien nay ung voi thanh mau trong BP
	UProgressBar* PlayerStaminaBar;

	UPROPERTY(meta = (BindWidget)) //Them macro nay thi bien nay ung voi thanh mau trong BP
	UProgressBar* BossHealthBar;

};
