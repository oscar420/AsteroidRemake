// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_PrimaryPojectile.h"

#include "DrawDebugHelpers.h"
#include "SCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

USAction_PrimaryPojectile::USAction_PrimaryPojectile()
{
	ShipSocketName1 = TEXT("Projectle Socket1");
	ShipSocketName2 = TEXT("Projectle Socket2");
}

void USAction_PrimaryPojectile::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	
	ASCharacter* Character = Cast<ASCharacter>(Instigator);

	if (ensureAlways(ProjectileClass && Character))
	{
		FVector SocketLocation1 = Character->SMesh->GetSocketLocation(ShipSocketName1);
		FVector SocketLocation2 = Character->SMesh->GetSocketLocation(ShipSocketName2);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = Character;
		

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
	
		FRotator CorrectRotation1 = FRotationMatrix::MakeFromX(TraceEnd - SocketLocation1).Rotator();
		FRotator CorrectRotation2 = FRotationMatrix::MakeFromX(TraceEnd - SocketLocation2).Rotator();
	
		FTransform SpawnTM1 = FTransform(CorrectRotation1, SocketLocation1);
		FTransform SpawnTM2 = FTransform(CorrectRotation2, SocketLocation2);
		
		//spawning is always done through the world
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM1, SpawnParams);
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM2, SpawnParams);
	}

	StopAction(Character);
}
