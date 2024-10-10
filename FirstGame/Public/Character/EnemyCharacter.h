
#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Interface/BossInterface.h"
#include "EnemyCharacter.generated.h"

class IAttackInterface;

UCLASS()
class FIRSTGAME_API AEnemyCharacter : public ABaseCharacter , public IBossInterface
{
	GENERATED_BODY()

public:
#pragma region Enemy_Interface
	virtual void I_HandleSeePlayer(AActor* PlayerActor) override;
	virtual FVector I_GetPatrolLocation() override;
	virtual void I_StopAttackAfterPlayerDead() override;
#pragma endregion

	virtual void Destroyed() override;
	virtual bool I_HasEnoughStamina(float CostStamina) const override;
	virtual void I_RequestAttack() override;

private:
	UPROPERTY()
	TScriptInterface<IAttackInterface> AttackInterface_Player;

	UPROPERTY(EditInstanceOnly, Category = "Patrol")
	TArray<AActor*> PatrolPoint;

	int PatrolIndex = 0;

	UPROPERTY()
	TScriptInterface<IAttackInterface> AttackInterface;

protected:
	virtual void HandleTakePointDame(AActor* DamagedActor, float Damage,
		class AController* InstigatedBy, FVector HitLocation,
		class UPrimitiveComponent* FHitComponent, FName BoneName,
		FVector ShotFromDirection, const class UDamageType* DamageType,
		AActor* DamageCauser) override;

	virtual void HandleDead() override;
};
