// Fill out your copyright notice in the Description page of Project Settings.


#include "SAsteroid.h"

#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "SGameplayFunctionLibrary.h"
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
	CapsuleComp->OnComponentHit.AddDynamic(this, &ASAsteroid::OnActorHit);

	ImpactDamage = 20.f;

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
	APawn* MyPawn = Cast<APawn>(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("ActorHited"));
	if (USGameplayFunctionLibrary::ApplyDirectionalDamage(this, OtherActor, ImpactDamage, Hit))
	{
		UPrimitiveComponent* HitComp = Hit.GetComponent();
		if (HitComp)
		{
			FVector Direction = Hit.TraceEnd - Hit.TraceStart;
			Direction.Normalize();
			HitComp->AddImpulseAtLocation(Direction * 30000.f, Hit.ImpactPoint);
		}
	}
}


void ASAsteroid::OnHealtChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	
	if (NewHealth <= 0.0f && Delta > 0.f)
	{
		Destroy();
	}
}
