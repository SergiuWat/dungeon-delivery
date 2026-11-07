// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HeroCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Character/SlowDamageEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/DOTDamageCharacter.h"
#include "TimerManager.h"
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

void AHeroCharacter::HandleDeath()
{
	if (bIsDead) return;

	bIsDead = true;
	OnHeroDied();
	Destroy();
}

void AHeroCharacter::ReceiveDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatorController, AActor* DamageCause)
{
	
	if (ASlowDamageEnemyCharacter* SlowDamageEnemy = Cast<ASlowDamageEnemyCharacter>(DamageCause))
	{
		Health = FMath::Clamp(Health - Damage, 0.f, MaxHealh);
		if (!bIsAlreadyAffectedBySlow)
		{
			//RestoreWalkSpeedAmount = SlowDamageEnemy->SlowAmount;
			//GetCharacterMovement()->MaxWalkSpeed -= SlowDamageEnemy->SlowAmount;
			bIsAlreadyAffectedBySlow = true;
			GetWorld()->GetTimerManager().SetTimer(SlowEffectTimerHandle, this, &ThisClass::SlowEffectFinished, 2.f, false);
		}

	}
	else if (ADOTDamageCharacter* DOTDamage = Cast<ADOTDamageCharacter>(DamageCause))
	{
		DOTDuration = DOTDamage->DOTDuration;
		if (bHasAlreadyDOT)
		{

			GetWorld()->GetTimerManager().SetTimer(DOTDurationHandle, this, &ThisClass::DOTDurationFinished, DOTDuration, false);
		}
		else
		{
			bHasAlreadyDOT = true;
			FTimerDelegate TickDelegate = FTimerDelegate::CreateUObject(this, &ThisClass::DOTTickDamageFinished, Damage);
			GetWorld()->GetTimerManager().SetTimer(DOTDurationHandle, this, &ThisClass::DOTDurationFinished, DOTDuration, false);
			GetWorld()->GetTimerManager().SetTimer(DOTTickDamageHandle, TickDelegate, DOTTickDamage, true);
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
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}

	if (Health <= 0.f)
	{		
		HandleDeath();
	}

}

void AHeroCharacter::SlowEffectFinished()
{
	GetCharacterMovement()->MaxWalkSpeed += RestoreWalkSpeedAmount;
	bIsAlreadyAffectedBySlow = false;
}

void AHeroCharacter::DOTDurationFinished()
{
	GetWorld()->GetTimerManager().ClearTimer(DOTTickDamageHandle);
	bHasAlreadyDOT = false;
}

void AHeroCharacter::DOTTickDamageFinished(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealh);

	if (Health <= 0.f)
	{
		HandleDeath();
	}
}


