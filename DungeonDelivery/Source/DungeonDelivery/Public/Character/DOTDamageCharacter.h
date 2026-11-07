// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayerCharacter.h"
#include "DOTDamageCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONDELIVERY_API ADOTDamageCharacter : public APlayerCharacter
{
	GENERATED_BODY()


public: 
	ADOTDamageCharacter();

	UPROPERTY(EditAnywhere)
	float DOTDuration = 10.f;

protected:

	
};
