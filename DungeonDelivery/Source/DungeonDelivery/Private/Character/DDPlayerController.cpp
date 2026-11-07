// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DDPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/Catapult.h"

void ADDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubsystem)) return;

	InputSubsystem->AddMappingContext(InputMappingContexts, 0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(MoveLauncherAction, ETriggerEvent::Triggered, this, &ThisClass::MoveLauncher);
	EnhancedInputComponent->BindAction(LaunchAction, ETriggerEvent::Started, this, &ThisClass::StartLaunchCharge);
	EnhancedInputComponent->BindAction(LaunchAction, ETriggerEvent::Completed, this, &ThisClass::Launch);
	EnhancedInputComponent->BindAction(LaunchAction, ETriggerEvent::Canceled, this, &ThisClass::CancelLaunchCharge);
}

float ADDPlayerController::GetLaunchChargePercent() const
{
	const ACatapult* Catapult = Cast<ACatapult>(GetPawn());
	if (!bIsChargingLaunch || !IsValid(Catapult)) return 0.f;

	const float HeldTime = GetWorld()->GetTimeSeconds() - ChargeStartTime;
	return FMath::Clamp(HeldTime / FMath::Max(Catapult->FullChargeTime, 0.01f), 0.f, 1.f);
}

void ADDPlayerController::StartLaunchCharge()
{

	if (!IsValid(Cast<ACatapult>(GetPawn()))) return;

	ChargeStartTime = GetWorld()->GetTimeSeconds();
	bIsChargingLaunch = true;
}

void ADDPlayerController::CancelLaunchCharge()
{
	bIsChargingLaunch = false;
}

void ADDPlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn())) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(FVector::UpVector, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
}

void ADDPlayerController::MoveLauncher(const FInputActionValue & Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	//AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void ADDPlayerController::Launch()
{
	if (!bIsChargingLaunch) return;

	const float ChargePercent = GetLaunchChargePercent();
	bIsChargingLaunch = false;
	if (ACatapult* Catapult = Cast<ACatapult>(GetPawn()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Launch"));
		Catapult->SpawnRandomEnemies(ChargePercent);
	}
}
