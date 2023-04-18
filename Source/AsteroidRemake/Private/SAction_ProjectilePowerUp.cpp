// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_ProjectilePowerUp.h"

#include "DrawDebugHelpers.h"
#include "SCharacter.h"


void USAction_ProjectilePowerUp::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	
	ASCharacter* Character = Cast<ASCharacter>(Instigator);

	if (ensureAlways(ProjectileClass && Character))
	{
	
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = Character;
		UE_LOG(LogTemp, Warning, TEXT("Intigator Action: %s"), *GetNameSafe(Character));

		FCollisionShape Shape;
		Shape.SetSphere(20.f);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(Character);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);
		ObjParams.AddObjectTypesToQuery(ECC_PhysicsBody);
		
		FHitResult Hit;
		ACharacter* InstigatorCharacter = Cast<ACharacter>(Instigator);
		if (!InstigatorCharacter)
		{
			return;
		}
		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation();
	
		FVector TraceEnd = TraceStart + (Character->GetControlRotation().Vector() * Range);
		
		bool bSucces = GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, QueryParams);
	
		if (bSucces)
		{
			TraceEnd = Hit.ImpactPoint;
			//DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 20.f, 32, FColor::Green, false, 2.0f);
		}
	
		
	
		FTransform SpawnTM1 = FTransform(InstigatorCharacter->GetControlRotation(), InstigatorCharacter->GetActorLocation());
		
		
		//spawning is always done through the world
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM1, SpawnParams);
		
	}

	StopAction(Character);
}
