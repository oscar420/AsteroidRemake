// Fill out your copyright notice in the Description page of Project Settings.


#include "SBasicProjectile.h"

#include "SActionComponent.h"
#include "SGameplayFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASBasicProjectile::ASBasicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp->SetCollisionProfileName(TEXT("Projectile"));
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASBasicProjectile::OnActorOverlap);

	InitialLifeSpan = 10.f;

	FlightLoopAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	FlightLoopAudio->SetupAttachment(SphereComp);
}

void ASBasicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
									   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		USActionComponent* ActionComp = Cast<USActionComponent>(OtherActor->GetComponentByClass(USActionComponent::StaticClass()));
		
		if (USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
		{
			Explode();
		}
	}
}