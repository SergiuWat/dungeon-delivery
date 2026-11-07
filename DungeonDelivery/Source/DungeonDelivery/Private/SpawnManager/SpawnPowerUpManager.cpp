// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager/SpawnPowerUpManager.h"
#include "Engine/TargetPoint.h"
#include "Engine/World.h"
#include "PowerUps/PoweUpBase.h"
// Sets default values
ASpawnPowerUpManager::ASpawnPowerUpManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ASpawnPowerUpManager::SpawnRandomPowerUp()
{
    TArray<ATargetPoint*> FreePoints;

    for (ATargetPoint* Point : SpawnPoints)
    {
        if (IsValid(Point) && !ActivePowerUps.FindRef(Point).IsValid())
        {
            FreePoints.AddUnique(Point);
        }
    }

    TArray<TSubclassOf<APoweUpBase>> ValidClasses;

    for (const TSubclassOf<APoweUpBase>& PowerUpClass : PowerUpClasses)
    {
        if (PowerUpClass)
        {
            ValidClasses.Add(PowerUpClass);
        }
    }

    if (FreePoints.IsEmpty() || ValidClasses.IsEmpty()) return;

    ATargetPoint* Point = FreePoints[FMath::RandHelper(FreePoints.Num())];
    const TSubclassOf<APoweUpBase> PowerUpClass = ValidClasses[FMath::RandHelper(ValidClasses.Num())];
    APoweUpBase* PowerUp = GetWorld()->SpawnActor<APoweUpBase>(PowerUpClass, Point->GetActorTransform());

    if (IsValid(PowerUp))
    {
        ActivePowerUps.Add(Point, PowerUp);
    }
}

// Called when the game starts or when spawned
void ASpawnPowerUpManager::BeginPlay()
{
	Super::BeginPlay();
	
    SpawnRandomPowerUp();

    if (SpawnInterval > 0.f)
    {
        GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ThisClass::SpawnRandomPowerUp, SpawnInterval, true);
    }
}

