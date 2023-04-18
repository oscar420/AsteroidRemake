// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDREMAKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	ASGameModeBase();

	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);
	
	UFUNCTION()
	void RespawnPlayerElpased(AController* Controller);
	
};
