// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Catapult.generated.h"

class USpringArmComponent;
class UCameraComponent;
class APlayerCharacter;
class USoundBase;

UCLASS()
class DUNGEONDELIVERY_API ACatapult : public APawn
{
	GENERATED_BODY()

public:

	ACatapult();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<APlayerCharacter>> CharactersToSpawn;

	UFUNCTION()
	void SpawnRandomEnemies(float ChargePercent);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseCanonMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CanonMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* PositionToSpawnEnemies;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* CannonPivot;

	UFUNCTION(BlueprintImplementableEvent, Category = "Cannon")
	void OnCannonFired();


	//UPROPERTY(VisibleAnywhere)
	//USceneComponent* AimPivot;

	UPROPERTY(EditAnywhere, Category = "Launch")
	float LaunchSpeed = 1800.f;

	UPROPERTY(EditAnywhere, Category = "Launch", meta = (ClampMin = "0.0"))
	float MaxLaunchSpeed = 3200.f;

	UPROPERTY(EditAnywhere, Category = "Launch", meta = (ClampMin = "0.01"))
	float FullChargeTime = 1.f;

	UPROPERTY(EditAnywhere)
	USoundBase* CannonFireSound;

protected:

	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;



};
