// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUps/IPowerUpInterface.h"
#include "PoweUpBase.generated.h"

class USphereComponent;

UCLASS()
class DUNGEONDELIVERY_API APoweUpBase : public AActor, public IIPowerUpInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoweUpBase();

	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionSphere;

	virtual void ActivatePowerUp(AActor* ActorToApplyEffect) override;

	UPROPERTY(EditAnywhere, Category = "PowerUp")
	float AddToSlowAmount = 50.f;

	UPROPERTY(EditAnywhere, Category = "PowerUp")
	float AddToRadialArea = 100.f;

	UPROPERTY(EditAnywhere, Category = "PowerUp")
	float AddToSlowDamage = 5.f;

	UPROPERTY(EditAnywhere, Category = "PowerUp")
	float AddToDOTDamage = 0.5f;

	UPROPERTY(EditAnywhere, Category = "PowerUp")
	float AddToDOTDuration = 2.f;

	UPROPERTY(EditAnywhere, Category = "PowerUp")
	float AddToDamage = 10.f;

	UPROPERTY(EditAnywhere, Category = "Floating", meta = (ClampMin = "0.0"))
	float FloatAmplitude = 2.f;

	UPROPERTY(EditAnywhere, Category = "Floating", meta = (ClampMin = "0.0"))
	float FloatFrequency = 0.2f;

	FVector FloatStartLocation = FVector::ZeroVector;
	float FloatElapsedTime = 0.f;
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	

	virtual void Tick(float DeltaTime) override;

};
