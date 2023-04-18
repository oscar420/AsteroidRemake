// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"

#include "SCharacter.h"

ASGameModeBase::ASGameModeBase()
{
}

void ASGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	ASCharacter* Player = Cast<ASCharacter>(VictimActor);
	if (Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;
		
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElpased", Player->GetController());

		float RespawnDelay = 2.f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);	
	}
}

void ASGameModeBase::RespawnPlayerElpased(AController* Controller)
{
	if (ensure(Controller))
	{
		Controller->UnPossess();
		
		RestartPlayer(Controller);	
	}
	
}