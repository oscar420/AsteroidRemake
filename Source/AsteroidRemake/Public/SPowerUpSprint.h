// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUpBase.h"
#include "SPowerUpSprint.generated.h"

class USAction;
class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class ASTEROIDREMAKE_API ASPowerUpSprint : public ASPowerUpBase
{
	GENERATED_BODY()

public:

	ASPowerUpSprint();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	FText GetInteractText_Implementation(APawn* InstigatorPawn) override;

protected:

	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category="Actions")
	TSubclassOf<USAction> ActionToAdd;
	
};
