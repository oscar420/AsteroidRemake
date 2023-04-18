// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectile.h"
#include "SBasicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UAudioComponent;
class USoundBase;
class USActionEffect;

/**
 * 
 */
UCLASS()
class ASTEROIDREMAKE_API ASBasicProjectile : public ASProjectile
{
	GENERATED_BODY()

public:
	
	// Sets default values for this actor's properties
	ASBasicProjectile();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	UAudioComponent* FlightLoopAudio;
	
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float DamageAmount = 20.f;
	
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	
};
