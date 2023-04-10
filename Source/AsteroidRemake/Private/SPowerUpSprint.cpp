// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpSprint.h"
#include "SAction.h"
#include "SActionComponent.h"

#define LOCTEXT_NAMESPACE "InteractableActors"

ASPowerUpSprint::ASPowerUpSprint()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void ASPowerUpSprint::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);

	if (!ensure(InstigatorPawn && ActionToAdd))
	{
		return;
	}

	USActionComponent* ActionComp = Cast<USActionComponent>(InstigatorPawn->GetComponentByClass(USActionComponent::StaticClass()));
	if (ActionComp && ActionComp->GetAction(ActionToAdd))
	{
		// Action already added
		return;
	}

	ActionComp->AddAction(InstigatorPawn, ActionToAdd);

	SetPowerUpState(false);
}

FText ASPowerUpSprint::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	return LOCTEXT("PowerUp_Description", "Use space button for max speed Up");
}

#undef LOCTEXT_NAMESPACE