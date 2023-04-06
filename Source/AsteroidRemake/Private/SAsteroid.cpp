// Fill out your copyright notice in the Description page of Project Settings.


#include "SAsteroid.h"

#include "SAttributeComponent.h"
#include "SProjectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
ASAsteroid::ASAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp= CreateDefaultSubobject<UCapsuleComponent>(TEXT("SphereComponent"));
	RootComponent = CapsuleComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CapsuleComp);

	RotComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingComp"));
	FRotator RotationRate= FRotator(FMath::RandRange(1.f, 4.f), FMath::RandRange(1.f, 4.f), FMath::RandRange(1.f, 4.f));
	RotComp->RotationRate = RotationRate;

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComp"));

	ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovComp"));
	ProjectileMoveComp->InitialSpeed = FMath::RandRange(100.f, 1000.f);
	ProjectileMoveComp->ProjectileGravityScale = 0.f;

	//CapsuleComp->OnComponentHit.AddDynamic(this, &ASAsteroid::OnActorHit);
	AttributeComp->OnHealtChange.AddDynamic(this, &ASAsteroid::OnHealtChange);

	bReplicates = true;
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

void ASAsteroid::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *GetNameSafe(OtherActor));
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *GetNameSafe(OtherComp));
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *GetNameSafe(HitComponent));
	ASProjectile* Projectile = Cast<ASProjectile>(OtherActor);
	
	if (Projectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *GetNameSafe(Projectile));
		Destroy();
	}
}

void ASAsteroid::OnHealtChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	UE_LOG(LogTemp, Warning, TEXT("NewHealth: %f"), NewHealth);
	UE_LOG(LogTemp, Warning, TEXT("Delta: %f"), Delta);
	if (NewHealth <= 0.0f && Delta > 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Destroyed"));
		Destroy();
	}
}
