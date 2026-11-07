// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HeroCharacter.generated.h"

UCLASS()
class DUNGEONDELIVERY_API AHeroCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AHeroCharacter();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ReceiveDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCause);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealh = 100.f;
protected:

	virtual void BeginPlay() override;

private:	



};
