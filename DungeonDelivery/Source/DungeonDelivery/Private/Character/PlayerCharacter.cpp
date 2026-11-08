// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Character/Catapult.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(CollisionSphere);


	TestMesh = CreateDefaultSubobject<UStaticMeshComponent>("TestMesh");
	TestMesh->SetupAttachment(CollisionSphere);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(CollisionSphere);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bUsePawnControlRotation = false;

	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 5.f;
	CameraBoom->CameraLagMaxDistance = 350.f;



	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionSphere);
	ProjectileMovementComponent->bRotationFollowsVelocity = false;

	DamageToCause = 20.f;

}

void APlayerCharacter::ApplySpeedBoos(float ForwardBoost, float UpwardBoost)
{
	FVector& Velocity = ProjectileMovementComponent->Velocity;
	const FVector FlightDirection = Velocity.GetSafeNormal2D();

	Velocity += FlightDirection * ForwardBoost;

	if (UpwardBoost > 0.f)
	{
		Velocity.Z = FMath::Max(Velocity.Z, UpwardBoost);
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	
}

void APlayerCharacter::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!IsValid(OtherActor) || OtherActor == this) return;

	AActor* DamageTarget = OtherActor;

	if (DamageTarget)
	{
		UGameplayStatics::ApplyDamage(DamageTarget, DamageToCause, GetInstigatorController(), this, UDamageType::StaticClass());

		FinishImpact();

		//APlayerController* PlayerController = Cast<APlayerController>(GetController());

		//if (IsValid(PlayerController) && IsValid(LaunchingCatapult))
		//{
		//	PlayerController->Possess(LaunchingCatapult);
		//	
		//	FViewTargetTransitionParams params;
		//	
		//	PlayerController->SetViewTarget(LaunchingCatapult, params);
		//}
	}

	//Destroy();
}

void APlayerCharacter::FinishImpact()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	AActor* Hero = ParryTarget.Get();

	if (!IsValid(PC) || !IsValid(Hero))
	{
		ReturnToCatapult();
		return;
	}

	ProjectileMovementComponent->Deactivate();
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);

	PC->SetViewTarget(Hero);

	FTimerHandle ParryTimer;
	GetWorldTimerManager().SetTimer(ParryTimer, this, &ThisClass::ReturnToCatapult, ReturnToCatapultTimer, false);
}

void APlayerCharacter::ReturnToCatapult()
{
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (IsValid(PC) && IsValid(LaunchingCatapult))
	{
		PC->Possess(LaunchingCatapult);
		PC->SetViewTarget(LaunchingCatapult);
	}

	Destroy();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector MovementInput = ConsumeMovementInputVector().GetClampedToMaxSize(1.f);
	const FVector LateralOffset = MovementInput * LateralMoveSpeed * DeltaTime;

	AddActorWorldOffset(LateralOffset, true);
}

void APlayerCharacter::LaunchProjectile(const FVector& LaunchVelocity)
{

	ProjectileMovementComponent->Velocity = LaunchVelocity;
}


