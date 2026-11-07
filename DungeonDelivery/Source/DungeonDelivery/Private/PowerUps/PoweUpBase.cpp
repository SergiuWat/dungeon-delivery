// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUps/PoweUpBase.h"
#include "Components/SphereComponent.h"
#include "Character/PlayerCharacter.h"
#include "Character/DOTDamageCharacter.h"
#include "Character/SlowDamageEnemyCharacter.h"

// Sets default values
APoweUpBase::APoweUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(CollisionSphere);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionSphere->SetGenerateOverlapEvents(true);
}


// Called when the game starts or when spawned
void APoweUpBase::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnPickupOverlap);
}

void APoweUpBase::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (!IsValid(PlayerCharacter)) return;

	ActivatePowerUp(PlayerCharacter);
	Destroy();
}

// Called every frame
void APoweUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FloatElapsedTime += DeltaTime;
	const float OffsetZ = FMath::Sin(FloatElapsedTime * FloatFrequency * 2.f * PI) * FloatAmplitude;
	const FVector NewLocation = GetActorLocation() + FVector(0.f, 0.f, OffsetZ);

	SetActorLocation(NewLocation, true);
}

void APoweUpBase::ActivatePowerUp(AActor* ActorToApplyEffect)
{
	if (ASlowDamageEnemyCharacter* SlowCharacter = Cast<ASlowDamageEnemyCharacter>(ActorToApplyEffect))
	{
		SlowCharacter->SlowAmount += AddToSlowAmount;
		SlowCharacter->RadialDamageArea += AddToRadialArea;
		SlowCharacter->DamageToCause += AddToSlowDamage;
	}
	else if (ADOTDamageCharacter* DOTCharacter = Cast<ADOTDamageCharacter>(ActorToApplyEffect))
	{
		DOTCharacter->DamageToCause += AddToDOTDamage;
		DOTCharacter->DOTDuration += AddToDOTDuration;
	}
	else if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(ActorToApplyEffect))
	{
		PlayerCharacter->DamageToCause += AddToDamage;
	}

}

