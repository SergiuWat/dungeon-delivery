// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SlowDamageEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Components/SphereComponent.h"
#include "Character/Catapult.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASlowDamageEnemyCharacter::ASlowDamageEnemyCharacter()
{
	DamageToCause = 5.f;
}

void ASlowDamageEnemyCharacter::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (!IsValid(OtherActor) || OtherActor == this) return;

	AActor* DamageTarget = OtherActor;
	
	if (DamageTarget)
	{
		UGameplayStatics::ApplyRadialDamage(this, DamageToCause, GetActorLocation(), RadialDamageArea, UDamageType::StaticClass(), TArray<AActor*>(), this, GetInstigatorController(), true);
		

		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
		
		FinishImpact();

		//DrawDebugSphere(GetWorld(), GetActorLocation(), RadialDamageArea, 24, FColor::Red, false, 3.f);
		

		/*APlayerController* PlayerController = Cast<APlayerController>(GetController());

		if (IsValid(PlayerController) && IsValid(LaunchingCatapult))
		{
			PlayerController->Possess(LaunchingCatapult);

			FViewTargetTransitionParams params;

			PlayerController->SetViewTarget(LaunchingCatapult, params);
		}*/
	}

	//Destroy();
}
