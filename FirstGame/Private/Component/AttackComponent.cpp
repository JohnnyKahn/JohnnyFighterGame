
#include "Component/AttackComponent.h"
#include "GameFramework/Character.h"
#include "DataAsset/BaseCharacterData.h"
#include "Interface/AttackInterface.h"
#include "Kismet/KismetSystemLibrary.h"

UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	//Kiem tra xem class co trien khai interface khong?
	AttackInterface = TScriptInterface<IAttackInterface>(GetOwner());
}

void UAttackComponent::RequestAttack()
{
	if (bCanAttack())
		Attack();
	else
		bSaveAttack = true;
}

bool UAttackComponent::bCanAttack() const
{
	if (AttackInterface == nullptr) return false;
	if (BaseCharacterData == nullptr) return false;

	const bool A = bIsAttacking == false || bCanCombo == true;
	const bool B = AttackInterface->I_HasEnoughStamina(BaseCharacterData->CostMap[RequestAttackType]);

	return A && B;

}

UAnimMontage* UAttackComponent::GetCorrectAttackMontage()
{	
	if (BaseCharacterData == nullptr) return nullptr;

	if (RequestAttackType == EAttackType::Super)
	{
		return BaseCharacterData->AttackMontage_Super;
	}

	if (BaseCharacterData->AttackMontage.IsEmpty()) return nullptr;

	return BaseCharacterData->AttackMontage[AttackIndex];
}


void UAttackComponent::Attack()
{
	if (AttackInterface && BaseCharacterData && GetCorrectAttackMontage())
	{
		AttackInterface->I_PlayAnimMontage(GetCorrectAttackMontage());
		AttackInterface->I_PlayStartAttackSound();
		bIsAttacking = true;
		bCanCombo = false;

		if (RequestAttackType == EAttackType::Normal)
			AttackIndex = (AttackIndex + 1) % BaseCharacterData->AttackMontage.Num();

		SuccessAttackCost = BaseCharacterData->CostMap[RequestAttackType];
		SuccessAttackDame = BaseCharacterData->DameMap[RequestAttackType];

		if (RequestAttackType == EAttackType::Normal) //Handle Attack Super
			AttackCount_Normal++;
		else
			AttackCount_Normal = 0;

		AttackInterface->I_HandleAttackSuccess();
	}
}

void UAttackComponent::SetupAttackComponent(UBaseCharacterData* BCD)
{
	BaseCharacterData = BCD;
}

void UAttackComponent::AN_EndAttack()
{
	bIsAttacking = false;
	bCanCombo = false;
	bSaveAttack = false;
	AttackIndex = 0;
}

void UAttackComponent::AN_Combo()
{
	bCanCombo = true;
	if (bSaveAttack)
	{
		RequestAttack();
		bSaveAttack = false;
	}
}

void UAttackComponent::SetupTraceHit() // Clear Array Actor Trace
{
	HitActor.Empty();
}

void UAttackComponent::TraceHit()
{
	if (AttackInterface == nullptr) return;
	if (BaseCharacterData == nullptr) return;

	const FVector& StartLocation = AttackInterface->I_GetSocketLocation(BaseCharacterData->TraceStart);
	const FVector& EndLocation = AttackInterface->I_GetSocketLocation(BaseCharacterData->TraceEnd);


	bool bDoHitSomething = UKismetSystemLibrary::SphereTraceMultiForObjects(
		this,
		StartLocation,
		EndLocation,
		BaseCharacterData->TraceRadius,
		BaseCharacterData->TraceObjectTypes,
		false,
		BaseCharacterData->ActorToIgnore,
		BaseCharacterData->bDrawDebugTrace? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		HitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		BaseCharacterData->Drawtime
	);

	if (bDoHitSomething == false) return;

	for (const FHitResult& Result : HitResult)
	{
		if (HitActor.Contains(Result.GetActor())) continue;

		HandleHitResult(Result);

		HitActor.Emplace(Result.GetActor());
	}
}

void UAttackComponent::HandleHitResult(const FHitResult& Result)
{
	if(HitSomethingDelegate.IsBound())
		HitSomethingDelegate.Execute(Result);
}



