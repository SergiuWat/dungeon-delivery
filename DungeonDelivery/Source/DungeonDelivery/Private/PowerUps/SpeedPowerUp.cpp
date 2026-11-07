// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUps/SpeedPowerUp.h"
#include "Components/SphereComponent.h"
#include "Character/PlayerCharacter.h"
#include "Character/DOTDamageCharacter.h"
#include "Character/SlowDamageEnemyCharacter.h"


void ASpeedPowerUp::ActivatePowerUp(AActor* ActorToApplyEffect)
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(ActorToApplyEffect))
	{
		PlayerCharacter->ApplySpeedBoos(ForwardSpeedBoost, UpwardSpeed);
	}
}
