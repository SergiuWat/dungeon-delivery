// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Catapult.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

ACatapult::ACatapult()
{

	PrimaryActorTick.bCanEverTick = true;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);


    BaseCanonMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseCannonMesh");
    BaseCanonMesh->SetupAttachment(GetRootComponent());

    CannonPivot = CreateDefaultSubobject<USceneComponent>(TEXT("CannonPivot"));
    CannonPivot->SetupAttachment(BaseCanonMesh);

    /*AimPivot = CreateDefaultSubobject<USceneComponent>(TEXT("AimPivot"));
    AimPivot->SetupAttachment(BaseCanonMesh);*/

    CanonMesh = CreateDefaultSubobject<UStaticMeshComponent>("CannonMesh");
    CanonMesh->SetupAttachment(CannonPivot);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	//CameraBoom->SetupAttachment(TestMesh);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

	PositionToSpawnEnemies = CreateDefaultSubobject<USceneComponent>("SpawnPositionComponent");
	//PositionToSpawnEnemies->SetupAttachment(GetRootComponent());

    PositionToSpawnEnemies->SetupAttachment(CannonPivot);
    CameraBoom->SetupAttachment(SceneRoot);
}

void ACatapult::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACatapult::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!IsValid(GetController())) return;

    CannonPivot->SetWorldRotation(GetControlRotation());

}

void ACatapult::SpawnRandomEnemies(float ChargePercent)
{
    AController* PlayerController = GetController();

    if (!PlayerController || CharactersToSpawn.IsEmpty())
        return;

    const int32 Index = FMath::RandRange(0, CharactersToSpawn.Num() - 1);

    const TSubclassOf<APlayerCharacter> EnemyClass =CharactersToSpawn[Index];

    if (!EnemyClass) return;

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride =ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
    

    APlayerCharacter* Enemy =GetWorld()->SpawnActor<APlayerCharacter>(EnemyClass,PositionToSpawnEnemies->GetComponentLocation(),FRotator::ZeroRotator,SpawnParams);

    if (!IsValid(Enemy)) return;

    Enemy->LaunchingCatapult = this;

    FVector LaunchDirection = PositionToSpawnEnemies->GetForwardVector();

    const float ShotSpeed = FMath::Lerp(LaunchSpeed, MaxLaunchSpeed, ChargePercent);
    Enemy->LaunchProjectile(LaunchDirection * ShotSpeed);

    if (CannonFireSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, CannonFireSound, GetActorLocation());
    }

    OnCannonFired();
    PlayerController->Possess(Enemy);

}



