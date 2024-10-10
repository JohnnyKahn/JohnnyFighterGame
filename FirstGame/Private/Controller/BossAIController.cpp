// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/BossAIController.h"
#include "Interface/BossInterface.h"
#include "Component/HealthComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Enum/AIState.h"

ABossAIController::ABossAIController()
{	
	//AI Perception Component
	AIPerceptionComponent = CreateDefaultSubobject
		<UAIPerceptionComponent>(TEXT("AI Perception Component"));

	// Sight Config
	AISightConfig = CreateDefaultSubobject
		<UAISenseConfig_Sight>(TEXT("AI Sight Config"));

	if (AISightConfig && AIPerceptionComponent)
	{
		AISightConfig->SightRadius = 2500.0f; //khoang cach nhin thay
		AISightConfig->LoseSightRadius = 2500.0f; //khoang cach mat dau
		AISightConfig->PeripheralVisionAngleDegrees = 360.0f;  //tam nhin boss
		AISightConfig->DetectionByAffiliation.bDetectNeutrals = true; //Set dong minh

		AIPerceptionComponent->ConfigureSense(*AISightConfig);
	}
}

void ABossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	BossInterface = TScriptInterface<IBossInterface>(InPawn);
	ProcessPawn = InPawn;
	//AddDynamic Event See Player

	RunBehaviorTree(BehaviorTree);

	if (AIPerceptionComponent)
		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic
		(this, &ABossAIController::HandleTargetPerciptionUpdate);

	
}


void ABossAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (ProcessPawn == nullptr) return;

	//UKismetSystemLibrary::DrawDebugCone(
	//	this,
	//	ProcessPawn->GetActorLocation(),
	//	ProcessPawn->GetActorForwardVector(),
	//	2500.0f,
	//	FMath::DegreesToRadians(360.0f),
	//	FMath::DegreesToRadians(360.0f),
	//	20,
	//	DebugColor,
	//	-1.0f,
	//	3.0f
	//	);
}

void ABossAIController::UpdatePatrolLocation()
{
	if (Blackboard && BossInterface)
	{
		Blackboard->SetValueAsVector(Key_PatrolLocation,
			BossInterface->I_GetPatrolLocation());
	}
	
}

void ABossAIController::CheckDistance(AActor* AIActor, AActor* PlayerActor, float AttackRange)
{
	if (PlayerActor == nullptr)
	{
		if (BossInterface && Blackboard)
		{
			Blackboard->SetValueAsEnum(Key_AIState, (uint8)EAIState::Combat);
			BossInterface->I_StopAttackAfterPlayerDead();
			return;
		}
	}

	if (bIsRegenHealth) return;

	if (AIActor == nullptr) return;

	auto Distance_AI_Player = AIActor->GetDistanceTo(PlayerActor);

	if (Distance_AI_Player <=  AttackRange)
	{
		if(Blackboard)
			Blackboard->SetValueAsEnum(Key_AIState, (uint8)EAIState::Attack);
	}
	else
	{
		if(Blackboard)
			Blackboard->SetValueAsEnum(Key_AIState, (uint8)EAIState::Combat);
	}
}

void ABossAIController::StartRegenHealth()
{
	bIsRegenHealth = true;

	if (Blackboard)
		Blackboard->SetValueAsEnum(Key_AIState, (uint8)EAIState::Regen);
}

void ABossAIController::HandleTargetPerciptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed()) //Khi thay 1 cai gi do
	{
		HandleSeePlayer(Actor);
	}
	else
	{
		DebugColor = FLinearColor::Green;
	}
}

void ABossAIController::HandleSeePlayer(AActor* Actor)
{
	DebugColor = FLinearColor::Red;
	//boss interface
	//thay nguoi choi
	if (BossInterface) {
		BossInterface->I_HandleSeePlayer(Actor);
	}
	if (Blackboard)
	{
		Blackboard->SetValueAsEnum(Key_AIState, (uint8)EAIState::Combat);
		Blackboard->SetValueAsObject(Key_PlayerActor, Actor);
	}
	
}
