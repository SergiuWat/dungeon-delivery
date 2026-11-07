// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUps/PoweUpBase.h"
#include "SpeedPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONDELIVERY_API ASpeedPowerUp : public APoweUpBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "PowerUp", meta = (ClampMin = "0.0"))
	float ForwardSpeedBoost = 600.f;

	UPROPERTY(EditAnywhere, Category = "PowerUp", meta = (ClampMin = "0.0"))
	float UpwardSpeed = 200.f;

	virtual void ActivatePowerUp(AActor* ActorToApplyEffect) override;


	
};
