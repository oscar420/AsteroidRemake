// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USActionComponent;
class USAttributeComponent;
class UParticleSystemComponent;

UCLASS()
class ASTEROIDREMAKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ASCharacter();

protected:

	UFUNCTION()
	void OnHealtChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float CurrentUpVelocity;

	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* CapsuleComp;
	
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float UpMaxVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Effects")
	UParticleSystemComponent* FlyEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Actions")
	USActionComponent* ActionComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CamaraComp;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	void PrimaryAttack();
	
	virtual void BeginPlay() override;
	
	/*UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewValue, float Delta);*/

	/** Bound to the thrust axis */
	void Thrust(float Val);

	/** Bound to the vertical axis */
	void MoveUp(float Val);

	/** Bound to the horizontal axis */
	void MoveRight(float Val);


public:	
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SMesh;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY()
	float Roll;

	
	UPROPERTY()
	float Pitch;
	
	/** How quickly forward speed changes */
	UPROPERTY(Category=Plane, EditAnywhere)
	float Acceleration;

	/** How quickly pawn can steer */
	UPROPERTY(Category=Plane, EditAnywhere)
	float TurnSpeed;

	/** Max forward speed */
	UPROPERTY(Category = Pitch, EditAnywhere)
	float MaxSpeed;

	/** Min forward speed */
	UPROPERTY(Category=Yaw, EditAnywhere)
	float MinSpeed;

	/** Current forward speed */
	float CurrentForwardSpeed;

	/** Current yaw speed */
	float CurrentYawSpeed;

	/** Current pitch speed */
	float CurrentPitchSpeed;

	/** Current roll speed */
	float CurrentRollSpeed;

};
