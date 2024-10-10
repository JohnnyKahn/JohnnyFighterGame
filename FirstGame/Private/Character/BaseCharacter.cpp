
#include "Character/BaseCharacter.h"



#include "GameFramework/CharacterMovementComponent.h"
#include "Component/AttackComponent.h"
#include "Component/HealthComponent.h"

#include "DataAsset/BaseCharacterData.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Components/CapsuleComponent.h"



ABaseCharacter::ABaseCharacter()
{

	PrimaryActorTick.bCanEverTick = false;


	//Tao AttackComponent
	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("Attack Component"));
	//Tao HealthComponent
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	//Cho nhan vat khong xoay khi camera xoay
	bUseControllerRotationYaw = false;
	//Cho huong nhan vat xoay theo khi di chuyen
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//Cho toc do xoay khi di chuyen
	GetCharacterMovement()->RotationRate.Yaw = 540.0;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

}

// Func nay duoc goi khi cac component da duoc tao ra
void ABaseCharacter::PostInitializeComponents()
{	
	Super::PostInitializeComponents();

	if (AttackComponent)
	{
		AttackComponent->HitSomethingDelegate.BindDynamic(this, &ABaseCharacter::HandleHitSomething);
		AttackComponent->SetupAttackComponent(BaseCharacterData);
	}
	if (HealthComponent) 
	{
		HealthComponent->SetupHealthComponent(BaseCharacterData);
	}
	
}
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnTakePointDamage.AddDynamic(this, &ABaseCharacter::HandleTakePointDame);

}

void ABaseCharacter::I_PlayAnimMontage(UAnimMontage* AttackMontage)
{
	PlayAnimMontage(AttackMontage);
}

void ABaseCharacter::I_PlayStartAttackSound()
{	
	if (BaseCharacterData == nullptr) return;
	UGameplayStatics::PlaySoundAtLocation
	(
		this,
		BaseCharacterData->StartAttackSound,
		GetActorLocation()
	);
}


#pragma region AttackInterface
void ABaseCharacter::I_EndAttack_AN()
{
	if (AttackComponent)
	{
		AttackComponent->AN_EndAttack();
	}
	
}

void ABaseCharacter::I_Combo_AN()
{
	if (AttackComponent)
	{
		AttackComponent->AN_Combo();
	}

}

FVector ABaseCharacter::I_GetSocketLocation(const FName& SocketName) const
{
	if (GetMesh() == nullptr) return FVector();
	return GetMesh()->GetSocketLocation(SocketName);
}

void ABaseCharacter::I_BeginTraceHit_ANS() //Begin trace clear array
{
	if (AttackComponent == nullptr) return;
	AttackComponent->SetupTraceHit();
}

void ABaseCharacter::I_RequestAttack()
{
	if (AttackComponent)
		AttackComponent->RequestAttack();
}

void ABaseCharacter::I_EndHitReact_AN()
{
	I_EndAttack_AN();

}

void ABaseCharacter::I_HandleAttackSuccess()
{
}

bool ABaseCharacter::I_IsAttacking() const
{
	if (AttackComponent == nullptr) return false;

	return AttackComponent->bIsAttacking;
	
}

void ABaseCharacter::I_TraceHit_ANS() //tracehit trong anim notify state
{	
	if (AttackComponent == nullptr) return;
	AttackComponent->TraceHit();
}
#pragma endregion



UAnimMontage* ABaseCharacter::GetCorrectHitReactMontage(const FVector AttackDirection) const
{	
	if(BaseCharacterData == nullptr) return nullptr;
	//Tich vo huong
	auto Dot = FVector::DotProduct(AttackDirection, GetActorForwardVector());

	const bool bShouldUseDot = FMath::Abs(Dot) > 0.5;

	if (FMath::Abs(Dot) > 0.5)
	{
		if (Dot > 0)
			return BaseCharacterData->HitReactMontage_Back;
		else
			return BaseCharacterData->HitReactMontage_Front;
	}
	else 
	{
		FVector Cross = FVector::CrossProduct(AttackDirection, GetActorForwardVector());
		if (Cross.Z > 0.0)
			return BaseCharacterData->HitReactMontage_Right;
		else
			return BaseCharacterData->HitReactMontage_Back;
	}
	

	return nullptr;
}

void ABaseCharacter::HandleHitSomething(const FHitResult& HitResult)
{
	if (BaseCharacterData == nullptr) return;
	if (AttackComponent == nullptr) return;

	auto HitActor = HitResult.GetActor();

	if (HitActor == nullptr) return;

	const auto AttackDirection = UKismetMathLibrary::GetDirectionUnitVector(
		GetActorLocation(),
		HitActor->GetActorLocation());

	UGameplayStatics::ApplyPointDamage(
		HitActor,
		AttackComponent->SuccessAttackDame, //dameMap
		AttackDirection,
		HitResult,
		GetController(),
		this,
		UDamageType::StaticClass()
	);
}

void ABaseCharacter::HandleTakePointDame(AActor* DamagedActor, float Damage, 
	AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, 
	FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, 
	AActor* DamageCauser)
{	
	SpawnHitImpact(HitLocation); // Spawn Effect
	
	if(HealthComponent)
		HealthComponent->UpdateHealthByDame(Damage);  //Update mau khi nhan dame

	if (HealthComponent->Health > 0.0f)
	{
		HandleBeaten(ShotFromDirection); // Handle khi bi danh
	}
	else
	{
		HandleDead();
	}
	
}

void ABaseCharacter::HandleBeaten(const FVector& ShotFromDirection)
{
	//Play Pain Sound
	if (BaseCharacterData == nullptr) return;

	UGameplayStatics::PlaySoundAtLocation
	(
		this,
		BaseCharacterData->PainSound,
		GetActorLocation()
	);
	//Hit React Montage
	PlayAnimMontage(GetCorrectHitReactMontage(ShotFromDirection));
}

void ABaseCharacter::HandleDead()
{
	//Play Dead Sound
	if (BaseCharacterData == nullptr) return;

	UGameplayStatics::PlaySoundAtLocation
	(
		this,
		BaseCharacterData->DeadSound,
		GetActorLocation()
	);
	//Hit React Montage
	float DeadMontageSecond = PlayAnimMontage(BaseCharacterData->DeadMontage);
	//CombatState = ECombatState::Dead;

	if (GetCharacterMovement()) //Dung di chuyen
		GetCharacterMovement()->StopMovementImmediately();

	if (GetCapsuleComponent() && GetMesh()) //Xoa Collision
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	SetLifeSpan(DeadMontageSecond);
	
}

void ABaseCharacter::SpawnHitImpact(const FVector& HitLocation)
{
	if (BaseCharacterData == nullptr) return;
	//Spawn Hit Impact Effect
	UGameplayStatics::SpawnEmitterAtLocation
	(GetWorld(),
		BaseCharacterData->HitImpactEffect,
		HitLocation
	);

	//Play Hit Impact Sound
	UGameplayStatics::PlaySoundAtLocation
	(
		this,
		BaseCharacterData->HitImpactSound,
		HitLocation
	);
}



