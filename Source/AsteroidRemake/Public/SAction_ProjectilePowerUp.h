// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SAction_ProjectilePowerUp.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDREMAKE_API USAction_ProjectilePowerUp : public USAction
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere)
	float Range = 10000000.f;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	UParticleSystem* ShootEffect;

public:
	
	//USAction_ProjectilePowerUp();
	
	virtual void StartAction_Implementation(AActor* Instigator) override;
	
};
