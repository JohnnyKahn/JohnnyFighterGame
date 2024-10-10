
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enum/AttackType.h"
#include "AttackComponent.generated.h"

//Khai bao Delegate
DECLARE_DYNAMIC_DELEGATE_OneParam(FHitSomethingDelegate, const FHitResult&, HitResult);

class UBaseCharacterData;
class IAttackInterface;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTGAME_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttackComponent();

	void RequestAttack();

	void SetupAttackComponent(UBaseCharacterData* BCD);

	void SetupTraceHit();

	void AN_EndAttack();
	void AN_Combo();

	void TraceHit();
	bool bIsAttacking = false;
	bool bCanCombo = false;

	float SuccessAttackCost = 0.0f;
	float SuccessAttackDame = 0.0f;
	
protected:
	virtual void BeginPlay() override;

	void HandleHitResult(const FHitResult& Result);

private:
	void Attack();
	UAnimMontage* GetCorrectAttackMontage();

public:
	FHitSomethingDelegate HitSomethingDelegate;
	EAttackType RequestAttackType = EAttackType::Normal;

	int AttackCount_Normal = 0;

private:
	UPROPERTY()
	TScriptInterface<IAttackInterface> AttackInterface;

	UPROPERTY()
	UBaseCharacterData* BaseCharacterData;

	TArray<FHitResult> HitResult;

	TArray<AActor*> HitActor;

	bool bCanAttack() const;


	bool bSaveAttack = false;
	int AttackIndex = 0;
};
