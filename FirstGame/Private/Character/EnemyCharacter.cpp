// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"
#include "Interface/AttackInterface.h"
#include "Component/HealthComponent.h"
#include "Component/AttackComponent.h"
#include "DataAsset/BaseCharacterData.h"

void AEnemyCharacter::I_HandleSeePlayer(AActor* PlayerActor)
{
	AttackInterface_Player = TScriptInterface<IAttackInterface>(PlayerActor);

	if (AttackInterface_Player && HealthComponent)
		AttackInterface_Player->I_EnterCombat(HealthComponent->Health / HealthComponent->MaxHealth);
}

FVector AEnemyCharacter::I_GetPatrolLocation()
{	
	if (PatrolPoint.IsEmpty()) return GetActorLocation();
	if (PatrolPoint[PatrolIndex] == nullptr) return GetActorLocation();

	auto ReturnValue = PatrolPoint[PatrolIndex]->GetActorLocation();
	PatrolIndex = (PatrolIndex + 1) % PatrolPoint.Num();
	return ReturnValue;
}

void AEnemyCharacter::I_StopAttackAfterPlayerDead()
{
	DetachFromControllerPendingDestroy();
}

void AEnemyCharacter::Destroyed()
{
	if (AttackInterface_Player) // goi truoc khi xoa ra khoi level
		AttackInterface_Player->I_HandleTargetDestroyed();

	Super::Destroyed();
}

bool AEnemyCharacter::I_HasEnoughStamina(float CostStamina) const
{
	return true;
}

void AEnemyCharacter::I_RequestAttack()
{
	if (AttackComponent == nullptr) return;

	if (AttackComponent->AttackCount_Normal >= 3)
	{
		AttackComponent->RequestAttackType = EAttackType::Super;
	}
	else
	{
		AttackComponent->RequestAttackType = EAttackType::Normal;
	}

	Super::I_RequestAttack();

}

void AEnemyCharacter::HandleTakePointDame(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	Super::HandleTakePointDame(DamagedActor, Damage, InstigatedBy, HitLocation, FHitComponent, BoneName, ShotFromDirection, DamageType, DamageCauser);

	if (AttackInterface_Player && HealthComponent)
		AttackInterface_Player->I_HitTarget(HealthComponent->Health / HealthComponent->MaxHealth);

}

void AEnemyCharacter::HandleDead()
{
	Super::HandleDead();
	
	DetachFromControllerPendingDestroy(); //Xoa Controller AI
}
