// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HeroCharacter.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AHeroCharacter::AHeroCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &AHeroCharacter::ReceiveDamage);
}

void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHeroCharacter::ReceiveDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatorController, AActor* DamageCause)
{
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealh);

	if (Health <= 0.f)
	{
		Destroy();
	}

}


