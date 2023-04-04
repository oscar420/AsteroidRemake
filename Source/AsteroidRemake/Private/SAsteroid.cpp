// Fill out your copyright notice in the Description page of Project Settings.


#include "SAsteroid.h"

#include "Components/SphereComponent.h"

// Sets default values
ASAsteroid::ASAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SphereComp);

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

