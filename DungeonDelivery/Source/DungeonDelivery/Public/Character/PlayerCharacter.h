// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USphereComponent;
class UProjectileMovementComponent;
class ACatapult;
class USoundBase;

UCLASS()
class DUNGEONDELIVERY_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:

	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TestMesh;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float LateralMoveSpeed = 600.f;

	UPROPERTY(EditAnywhere)
	float DamageToCause;

	void LaunchProjectile(const FVector& LaunchVelocity);

	UPROPERTY()
	ACatapult* LaunchingCatapult = nullptr;

	void ApplySpeedBoos(float ForwardBoost, float UpwardBoost);

	void MarkParried(AActor* Hero) { ParryTarget = Hero; }

	UPROPERTY(EditAnywhere)
	float ReturnToCatapultTimer = 0.5f;

	UPROPERTY(EditAnywhere)
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionSphere;

	void FinishImpact();
	bool bImpactHandled = false;

private:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	TWeakObjectPtr<AActor> ParryTarget;
	void ReturnToCatapult();


};
