// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DOTDamageCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Components/SphereComponent.h"
#include "Character/Catapult.h"

ADOTDamageCharacter::ADOTDamageCharacter()
{
	DamageToCause = 1.f;
}
