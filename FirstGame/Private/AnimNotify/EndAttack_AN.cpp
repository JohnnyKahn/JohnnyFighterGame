
#include "AnimNotify/EndAttack_AN.h"
#include "Interface/AttackInterface.h"

void UEndAttack_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr)
		return;

	auto AttackInterface =
		TScriptInterface<IAttackInterface>(MeshComp->GetOwner());

	if (AttackInterface)
		AttackInterface->I_EndAttack_AN();
}
