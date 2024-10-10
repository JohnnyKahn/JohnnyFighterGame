// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class FIRSTGAME_API UEndWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	void UpdateResultText(FText NewText);

private:
	UFUNCTION()
	void PlayAgainClick();

	UFUNCTION()
	void ExitClick();

private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResultText;

	UPROPERTY(meta = (BindWidget))
	UButton* PlayAgainButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

};
