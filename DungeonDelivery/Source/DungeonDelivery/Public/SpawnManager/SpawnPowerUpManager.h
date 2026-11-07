// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "SpawnPowerUpManager.generated.h"

class ATargetPoint;
class APoweUpBase;
UCLASS()
class DUNGEONDELIVERY_API ASpawnPowerUpManager : public AActor
{
	GENERATED_BODY()
	
public:	

	ASpawnPowerUpManager();

	UPROPERTY(EditInstanceOnly, Category = "Power Ups")
	TArray<TObjectPtr<ATargetPoint>> SpawnPoints;

	UPROPERTY(EditAnywhere, Category = "Power Ups")
	TArray<TSubclassOf<APoweUpBase>> PowerUpClasses;

	UPROPERTY(EditAnywhere, Category = "Power Ups", meta = (ClampMin = "0.0"))
	float SpawnInterval = 5.f;

	TMap<ATargetPoint*, TWeakObjectPtr<APoweUpBase>> ActivePowerUps;
	FTimerHandle SpawnTimerHandle;

	UFUNCTION()
	void SpawnRandomPowerUp();

protected:

	virtual void BeginPlay() override;
};
