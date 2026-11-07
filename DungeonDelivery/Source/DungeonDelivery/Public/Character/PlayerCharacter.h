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

	void LaunchProjectile(const FVector& LaunchVelocity);

	UPROPERTY()
	TObjectPtr<ACatapult> LaunchingCatapult = nullptr;
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionSphere;

private:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

};
