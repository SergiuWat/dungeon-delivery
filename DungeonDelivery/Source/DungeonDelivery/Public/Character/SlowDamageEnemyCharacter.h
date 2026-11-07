// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayerCharacter.h"
#include "SlowDamageEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONDELIVERY_API ASlowDamageEnemyCharacter : public APlayerCharacter
{
	GENERATED_BODY()
public:

	ASlowDamageEnemyCharacter();

	UPROPERTY(EditAnywhere)
	float SlowAmount = 400.f;

	UPROPERTY(EditAnywhere)
	float RadialDamageArea = 400.f;

protected:

	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;



};
