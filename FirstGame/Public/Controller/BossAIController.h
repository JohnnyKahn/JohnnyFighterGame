// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossAIController.generated.h"

class UAISenseConfig_Sight;
class IBossInterface;
class UHealthComponent;
		
UCLASS()
class FIRSTGAME_API ABossAIController : public AAIController
{
	GENERATED_BODY()
public:
	ABossAIController();
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void UpdatePatrolLocation();

	UFUNCTION(BlueprintCallable)
	void CheckDistance(AActor* AIActor, AActor* PlayerActor, float AttackRange);

	void StartRegenHealth();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	

private:
	UFUNCTION()
	void HandleTargetPerciptionUpdate(AActor* Actor, FAIStimulus Stimulus);

	void HandleSeePlayer(AActor* Actor);

	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComponent;




private:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere)
	UAISenseConfig_Sight* AISightConfig;

	UPROPERTY(EditDefaultsOnly)
	FName Key_PlayerActor;

	UPROPERTY(EditDefaultsOnly)
	FName Key_PatrolLocation;

	UPROPERTY(EditDefaultsOnly)
	FName Key_AIState;

	UPROPERTY()
	APawn* ProcessPawn;

	UPROPERTY()
	TScriptInterface<IBossInterface> BossInterface; //Boss Interface

	FLinearColor DebugColor = FLinearColor::Green;

	bool bIsRegenHealth = false;
	
};
