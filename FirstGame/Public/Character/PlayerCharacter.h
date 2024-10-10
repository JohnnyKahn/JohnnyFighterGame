// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UPlayerWidget;
class UStaminaComponent;
class UEndWidget;

UCLASS()
class FIRSTGAME_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	//Contructor
	APlayerCharacter();
	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Destroyed() override;

#pragma region Attack_Interface
	virtual void I_EnterCombat(float NewPercentHealthBoss) override;
	virtual void I_HitTarget(float NewPercentTarget) override;
	virtual void I_HandleTargetDestroyed() override;
	virtual void I_HandleAttackSuccess() override;
	virtual bool I_HasEnoughStamina(float CostStamina) const override;
	virtual void I_StaminaUpdate() override;

#pragma endregion

protected:
	virtual void BeginPlay() override;
	virtual void HandleTakePointDame(AActor* DamagedActor, float Damage,
		class AController* InstigatedBy, FVector HitLocation,
		class UPrimitiveComponent* FHitComponent, FName BoneName,
		FVector ShotFromDirection, const class UDamageType* DamageType,
		AActor* DamageCauser) override;
	virtual void HandleDead() override;

	virtual void HandleBeaten(const FVector& ShotFromDirection) override;
	
private:
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);

	void AttackPress();
	
	void SuperAttackPress();

	void AddMappingContextForCharacter();

	void ShowEndWidget(FText ResultText);

	void PauseGame();


private:
	FText LoseText = FText::FromString(TEXT("Lose"));
	FText WinText = FText::FromString(TEXT("Win"));


	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> PlayerWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> EndWidgetClass;

	UPROPERTY()
	UPlayerWidget* PlayerWidget;

	UPROPERTY()
	UEndWidget* EndWidget;

	UPROPERTY(VisibleAnyWhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnyWhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	UStaminaComponent* StaminaComponent;

	int KillCount = 0;
};
