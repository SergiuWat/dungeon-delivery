// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HeroCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Character/SlowDamageEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
AHeroCharacter::AHeroCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}



void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &AHeroCharacter::ReceiveDamage);
}

void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHeroCharacter::ReceiveDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatorController, AActor* DamageCause)
{
	
	if (ASlowDamageEnemyCharacter* SlowDamageEnemy = Cast<ASlowDamageEnemyCharacter>(DamageCause))
	{
		if (!bIsAlreadyAffectedBySlow)
		{
			Health = FMath::Clamp(Health - Damage, 0.f, MaxHealh);
			RestoreWalkSpeedAmount = SlowDamageEnemy->SlowAmount;
			GetCharacterMovement()->MaxWalkSpeed -= SlowDamageEnemy->SlowAmount;
			bIsAlreadyAffectedBySlow = true;
			GetWorld()->GetTimerManager().SetTimer(SlowEffectTimerHandle, this, &ThisClass::SlowEffectFinished, 2.f, false);
		}

	}
	else if (IsValid(DamageCause))
	{
		Health = FMath::Clamp(Health - Damage, 0.f, MaxHealh);
	}
	else
	{
		return;
	}
	

	if (Health <= 0.f)
	{		
		Destroy();
	}

}

void AHeroCharacter::SlowEffectFinished()
{
	GetCharacterMovement()->MaxWalkSpeed += RestoreWalkSpeedAmount;
	bIsAlreadyAffectedBySlow = false;
}


