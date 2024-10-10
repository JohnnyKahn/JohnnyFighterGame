
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enum/AttackType.h"
#include "BaseCharacterData.generated.h"


class UAnimMontage;
class UParticleSystem;
class USoundBase;

UCLASS()
class FIRSTGAME_API UBaseCharacterData : public UDataAsset
{
	GENERATED_BODY()

public:
	UBaseCharacterData();

public:
	/* Attack*/
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TArray<UAnimMontage*> AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	UAnimMontage* AttackMontage_Super;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TMap<EAttackType, float> CostMap; //Map tuong tu nhu Dictionary cua C# gom 1 cap key-value

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TMap<EAttackType, float> DameMap;

	/* Hit Impact*/
	UPROPERTY(EditDefaultsOnly, Category = "Hit Impact")
	UParticleSystem* HitImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* HitImpactSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* PainSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* StartAttackSound;

	/* Dead */
	UPROPERTY(EditDefaultsOnly, Category = "Hit React")
	UAnimMontage* DeadMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Dead")
	USoundBase* DeadSound;

	/* Hit React Montage*/
	
	UPROPERTY(EditDefaultsOnly, Category = "Hit React")
	UAnimMontage* HitReactMontage_Front;

	UPROPERTY(EditDefaultsOnly, Category = "Hit React")
	UAnimMontage* HitReactMontage_Back;

	UPROPERTY(EditDefaultsOnly, Category = "Hit React")
	UAnimMontage* HitReactMontage_Left;

	UPROPERTY(EditDefaultsOnly, Category = "Hit React")
	UAnimMontage* HitReactMontage_Right;

	UPROPERTY(EditDefaultsOnly, Category = "Trace Hit")
	FName TraceStart;

	UPROPERTY(EditDefaultsOnly, Category = "Trace Hit")
	FName TraceEnd;

	UPROPERTY(EditDefaultsOnly, Category = "Trace Hit")
	float TraceRadius = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Trace Hit")
	TArray<AActor*> ActorToIgnore;

	UPROPERTY(EditDefaultsOnly, Category = "Trace Hit")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	UPROPERTY(EditDefaultsOnly, Category = "Trace Hit")
	float Drawtime = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Trace Hit")
	bool bDrawDebugTrace = true;

	/*Stat*/

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float Health = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float Stamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float MaxStamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float RegenSpeed = 40.0f;

	/*Sound*/

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ThemeSound;

	/*Shake Camera*/
	UPROPERTY(EditDefaultsOnly, Category = "Shake")
	TSubclassOf<UCameraShakeBase> CameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Shake")
	float ShakeScale = 10.0f;
};
