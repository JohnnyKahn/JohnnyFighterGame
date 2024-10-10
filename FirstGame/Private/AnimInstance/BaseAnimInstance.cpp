// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/BaseAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{	
	//TrygetPawn tra ve Pawn dang so huu AnimInstance
	Character = Cast<ACharacter>(TryGetPawnOwner());

	if(Character)
	MovementComponent = Character->GetCharacterMovement();

}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{	
	//Tinh do lon cua van toc 
	if (MovementComponent == nullptr)
		return;
	GroundSpeed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);

	//Dieu kien Idle -> Run va Run -> Idle
	if (GroundSpeed > 0.0f) {
		bShouldMove = true;
	}
	else if (GroundSpeed == 0) {
		bShouldMove = false;
	}

	/*Strafing*/
	const auto& AimRotation = Character->GetBaseAimRotation();

	const auto MovementRotation =
		UKismetMathLibrary::MakeRotFromX(Character->GetVelocity());

	StrafingValue = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
}
