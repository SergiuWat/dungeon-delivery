// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HeroCharacter.generated.h"

class USoundBase;

UCLASS()
class DUNGEONDELIVERY_API AHeroCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AHeroCharacter();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	bool bIsDead = false;

	UFUNCTION(BlueprintImplementableEvent, Category = "Hero")
	void OnHeroDied();

	void HandleDeath();

	UFUNCTION()
	void ReceiveDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCause);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealh = 100.f;

	float RestoreWalkSpeedAmount;

	FTimerHandle SlowEffectTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> HitSound = nullptr;

	UFUNCTION()
	void SlowEffectFinished();

	bool  bIsAlreadyAffectedBySlow = false;

	FTimerHandle DOTDurationHandle;

	UFUNCTION()
	void DOTDurationFinished();

	FTimerHandle DOTTickDamageHandle;

	UFUNCTION()
	void DOTTickDamageFinished(float Damage);

	UPROPERTY(EditAnywhere)
	float DOTDuration = 10.f;

	UPROPERTY(EditAnywhere)
	float DOTTickDamage = 0.5f;

	bool bHasAlreadyDOT = false;

	UPROPERTY(EditAnywhere, Category = "Parry", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float ParryChance = 0.25f;

	UFUNCTION(BlueprintImplementableEvent, Category = "Parry")
	void OnHeroParried();
protected:

	virtual void BeginPlay() override;

private:	



};
