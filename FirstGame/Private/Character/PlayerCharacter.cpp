// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "Widget/PlayerWidget.h"
#include "Widget/EndWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Component/HealthComponent.h"
#include "Component/StaminaComponent.h"
#include "Component/AttackComponent.h"
#include "Interface/AttackInterface.h"
#include "DataAsset/EnhaceInputData.h"
#include "DataAsset/BaseCharacterData.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"

APlayerCharacter::APlayerCharacter()
{
	//SpringArm
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 400.0f;
	SpringArmComponent->AddLocalOffset(FVector(0.0, 0.0, 40.0));

	//Dung chung Rotation voi Controller
	SpringArmComponent->bUsePawnControlRotation = true;

	//camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	StaminaComponent = CreateDefaultSubobject<UStaminaComponent>(TEXT("Stamina Component"));
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (StaminaComponent)
	{
		StaminaComponent->SetupStaminaComponent(BaseCharacterData);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	AddMappingContextForCharacter();

	//Bind Input Action
	UEnhancedInputComponent* EnhancedInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent && EnhaceInputData)
	{
		EnhancedInputComponent->BindAction(EnhaceInputData->IA_Look, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		EnhancedInputComponent->BindAction(EnhaceInputData->IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		EnhancedInputComponent->BindAction(EnhaceInputData->IA_Attack, ETriggerEvent::Started, this, &APlayerCharacter::AttackPress);

		EnhancedInputComponent->BindAction(EnhaceInputData->IA_SuperAttack, ETriggerEvent::Started, this, &APlayerCharacter::SuperAttackPress);
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Tao Widget
	PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);
	
	//Them Widget vao man hinh
	if (PlayerWidget && HealthComponent && StaminaComponent)
	{
		PlayerWidget->AddToViewport();
		PlayerWidget->UpdataHealthBarPlayer(HealthComponent->Health / HealthComponent->MaxHealth);
		PlayerWidget->UpdataStaminaBarPlayer(StaminaComponent->Stamina / StaminaComponent->MaxStamina);
	}
	if (BaseCharacterData)
		UGameplayStatics::SpawnSound2D(this, BaseCharacterData->ThemeSound); //SoundBackground
}

void APlayerCharacter::Destroyed()
{
	Super::Destroyed();
}

void APlayerCharacter::ShowEndWidget(FText ResultText)
{	
	auto PlayerController = Cast<APlayerController>(GetController());
	if (EndWidget == nullptr)
		EndWidget = CreateWidget<UEndWidget>(PlayerController, EndWidgetClass);

	if (PlayerController == nullptr) return;
	if (EndWidget == nullptr) return;

	//FTimerHandle TimerHandle;
	//if (!GetWorldTimerManager().IsTimerActive(TimerHandle))
	//{
	//	GetWorldTimerManager().SetTimer(TimerHandle, this, &UGameplayStatics::SetGamePaused, 1.0f, false);
	//}
	
	PauseGame();

	EndWidget->AddToViewport();//Them Widget vao man hinh
	EndWidget->UpdateResultText(ResultText);

	FInputModeUIOnly MyInputMode;
	MyInputMode.SetWidgetToFocus(EndWidget->TakeWidget());

	PlayerController->SetInputMode(MyInputMode);
	PlayerController->SetShowMouseCursor(true);
}

void APlayerCharacter::PauseGame()
{
	UGameplayStatics::SetGamePaused(this, true);
}


void APlayerCharacter::HandleTakePointDame(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	Super::HandleTakePointDame(DamagedActor, Damage, InstigatedBy, HitLocation, FHitComponent, BoneName, ShotFromDirection, DamageType, DamageCauser);
	if(PlayerWidget && HealthComponent)
		PlayerWidget->UpdataHealthBarPlayer(
			HealthComponent->Health/HealthComponent->MaxHealth);
}

void APlayerCharacter::HandleDead()
{
	Super::HandleDead();

	if(PlayerWidget)
		PlayerWidget->RemoveFromParent();

	auto PlayerController = Cast<APlayerController>(GetController());
	DisableInput(PlayerController); //Tat PlayerController sau khi chet

	ShowEndWidget(LoseText);
}

void APlayerCharacter::HandleBeaten(const FVector& ShotFromDirection)
{
	Super::HandleBeaten(ShotFromDirection);
	auto CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);

	if (CameraManager && BaseCharacterData)
	{
		CameraManager->StartCameraShake(
			BaseCharacterData->CameraShakeClass,
			BaseCharacterData->ShakeScale); //Shake Camera
	}

}


void APlayerCharacter::I_EnterCombat(float NewPercentHealthBoss)
{	
	if(PlayerWidget)
		PlayerWidget->UpdataHealthBarEnemy(NewPercentHealthBoss);
}

void APlayerCharacter::I_HitTarget(float NewPercentTarget)
{
	if (PlayerWidget)
		PlayerWidget->UpdataHealthBarEnemy(NewPercentTarget);
}

void APlayerCharacter::I_HandleTargetDestroyed()
{
	KillCount++;

	if (PlayerWidget)
		PlayerWidget->HideEnemyStats();

	if (KillCount >= 1)
	{
		ShowEndWidget(WinText);
	}

}

void APlayerCharacter::I_HandleAttackSuccess() // Tru Stamina khi attack
{
	if (StaminaComponent && PlayerWidget && AttackComponent)
	{
		StaminaComponent->UpdateStamina(AttackComponent->SuccessAttackCost);
		PlayerWidget->UpdataStaminaBarPlayer(StaminaComponent->Stamina / StaminaComponent->MaxStamina);
	}
}

bool APlayerCharacter::I_HasEnoughStamina(float CostStamina) const
{
	if (StaminaComponent == nullptr) return false;

	return StaminaComponent->Stamina >= CostStamina;
}

void APlayerCharacter::I_StaminaUpdate()
{
	if (StaminaComponent && PlayerWidget)
	{
		PlayerWidget->UpdataStaminaBarPlayer(StaminaComponent->Stamina / StaminaComponent->MaxStamina);
	}
}

#pragma region Input

void APlayerCharacter::AddMappingContextForCharacter()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController == nullptr)
		return;
	UEnhancedInputLocalPlayerSubsystem* Subsystem
		= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
		(PlayerController->GetLocalPlayer());

	if (Subsystem && EnhaceInputData)
		Subsystem->AddMappingContext(EnhaceInputData->InputMappingContext, 0);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();

	if (LookValue.X != 0.0)
		AddControllerYawInput(LookValue.X);

	if (LookValue.Y != 0.0)
		AddControllerPitchInput(LookValue.Y);
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{

	const FVector2D ActionValue = Value.Get<FVector2D>();

	const FRotator MyControllerRotation = FRotator(0.0, GetControlRotation().Yaw, 0.0);
	//Di chuyen len tren - xuong duoi
	const FVector ForwardDirection
		= MyControllerRotation.RotateVector(FVector::ForwardVector);

	if (ActionValue.Y != 0.0 && AttackComponent->bIsAttacking == false)
	{
		AddMovementInput(ForwardDirection, ActionValue.Y);
	} // Khi dang tan cong thi khong di chuyen duoc 
	else
	{
		AddMovementInput(FVector(0.0, 0.0, 0.0), ActionValue.Y);
	}

	//Di chuyen trai - phai
	const FVector RightLeftDirection
		= MyControllerRotation.RotateVector(FVector::RightVector);

	if (ActionValue.X != 0.0 && AttackComponent->bIsAttacking == false)
	{
		AddMovementInput(RightLeftDirection, ActionValue.X);
	} // Khi dang tan cong thi khong di chuyen duoc 
	else
	{
		AddMovementInput(FVector(0.0, 0.0, 0.0), ActionValue.X);
	}

}

void APlayerCharacter::AttackPress()
{
	//normal attack
	AttackComponent->RequestAttackType = EAttackType::Normal;
	I_RequestAttack();
}

void APlayerCharacter::SuperAttackPress()
{
	//strong attack
	AttackComponent->RequestAttackType = EAttackType::Super;
	I_RequestAttack();
}

#pragma endregion

