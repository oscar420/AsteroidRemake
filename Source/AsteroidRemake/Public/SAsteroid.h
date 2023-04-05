// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SAsteroid.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class URotatingMovementComponent;
class UProjectileMovementComponent;

UCLASS()
class ASTEROIDREMAKE_API ASAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASAsteroid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	URotatingMovementComponent* RotComp;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	UProjectileMovementComponent* ProjectileMoveComp;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
