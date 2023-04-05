// Fill out your copyright notice in the Description page of Project Settings.


#include "SAsteroid.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
ASAsteroid::ASAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SphereComp);

	RotComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingComp"));
	FRotator RotationRate= FRotator(FMath::RandRange(1.f, 4.f), FMath::RandRange(1.f, 4.f), FMath::RandRange(1.f, 4.f));
	RotComp->RotationRate = RotationRate;

	ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovComp"));
	ProjectileMoveComp->InitialSpeed = FMath::RandRange(100.f, 1000.f);
	ProjectileMoveComp->ProjectileGravityScale = 0.f;

}

// Called when the game starts or when spawned
void ASAsteroid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

