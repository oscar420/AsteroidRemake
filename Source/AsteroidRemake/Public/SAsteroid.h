// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SAsteroid.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;
class URotatingMovementComponent;
class UProjectileMovementComponent;
class USAttributeComponent;

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

	UPROPERTY(EditDefaultsOnly)
	float ImpactDamage;

	UFUNCTION()
	void OnHealtChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USAttributeComponent* AttributeComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	URotatingMovementComponent* RotComp;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	UProjectileMovementComponent* ProjectileMoveComp;
	
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
