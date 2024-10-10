// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerWidget.h"
#include "Components/ProgressBar.h" //folder cua unreal

void UPlayerWidget::UpdataHealthBarPlayer(float NewPercent)
{
	if (PlayerHealthBar)
	{
		PlayerHealthBar->SetPercent(NewPercent);
	}
	
}

void UPlayerWidget::UpdataStaminaBarPlayer(float NewPercent)
{
	if (PlayerStaminaBar)
	{
		PlayerStaminaBar->SetPercent(NewPercent);
	}
}

void UPlayerWidget::UpdataHealthBarEnemy(float NewPercent)
{
	if (BossHealthBar)
	{
		BossHealthBar->SetPercent(NewPercent);
	}
}

void UPlayerWidget::HideEnemyStats()
{
	if (BossHealthBar)
	{
		BossHealthBar->SetVisibility(ESlateVisibility::Hidden);
		BossHealthBar->SetVisibility(ESlateVisibility::Hidden);
	}
}
