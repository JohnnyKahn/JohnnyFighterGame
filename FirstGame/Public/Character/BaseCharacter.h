#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/AttackInterface.h"
#include "BaseCharacter.generated.h"


class UInputMappingContext;
class UInputAction;
class UEnhaceInputData;
struct FInputActionValue;
class UAttackComponent;
class UHealthComponent;
class UBaseCharacterData;
class UStaminaComponent;

UCLASS()
class FIRSTGAME_API ABaseCharacter :
	public ACharacter,
	public IAttackInterface

{
	GENERATED_BODY()

public:

	ABaseCharacter();
	
	virtual void PostInitializeComponents() override;
	// Interface
	virtual void I_PlayAnimMontage(UAnimMontage* AttackMontage) override;
	virtual void I_PlayStartAttackSound() override;
	virtual void I_EndAttack_AN() override;
	virtual void I_Combo_AN() override;
	virtual FVector I_GetSocketLocation(const FName& SocketName) const override;
	virtual void I_TraceHit_ANS() override;
	virtual void I_BeginTraceHit_ANS() override;
	virtual void I_RequestAttack() override;
	virtual void I_EndHitReact_AN() override;
	virtual void I_HandleAttackSuccess() override; //Tru Stamina
	virtual bool I_IsAttacking() const override;
	
protected:

	virtual void BeginPlay() override;

	virtual void HandleBeaten(const FVector& ShotFromDirection);

	UFUNCTION() // Func dang ki delegate nen phai co UFUNCTION()
	virtual void HandleTakePointDame(AActor* DamagedActor, float Damage,
			class AController* InstigatedBy, FVector HitLocation,
			class UPrimitiveComponent* FHitComponent, FName BoneName,
			FVector ShotFromDirection, const class UDamageType* DamageType,
			AActor* DamageCauser);

	UPROPERTY(VisibleAnywhere)
	UAttackComponent* AttackComponent;

	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Character Data Assets")
	UEnhaceInputData* EnhaceInputData;

	virtual void HandleDead();

	UPROPERTY(EditDefaultsOnly, Category = "Character Data Assets")
	UBaseCharacterData* BaseCharacterData;


private:
	UAnimMontage* GetCorrectHitReactMontage(const FVector AttackDirection) const;

	//Event Func
	UFUNCTION() // Func dang ki delegate nen phai co UFUNCTION()
	void HandleHitSomething(const FHitResult& HitResult);

	void SpawnHitImpact(const FVector& HitLocation);




};