// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "SActionComponent.h"
#include "SAttributeComponent.h"
#include "SInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	// Create Capsule Component
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CapsuleComp->SetupAttachment(RootComponent);

	// Create Interaction Component
	InteractionComp = CreateDefaultSubobject<USInteractionComponent>(TEXT("InteractionComp"));

	// Create static mesh component
	SMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SMesh->SetupAttachment(RootComponent);

	// Create a spring arm component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	// Create camera component 
	CamaraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CamaraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	// Create Action Component
	ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComp");

	// Create Attribute Component
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComp"));
	AttributeComp->OnHealtChange.AddDynamic(this, &ASCharacter::OnHealtChange);

	// Create Fly Effect Component
	FlyEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FlyEffect"));
	FlyEffect->SetupAttachment(SMesh);
	
	// Set handling parameters
	Acceleration = 500.f;
	TurnSpeed = 50.f;
	MaxSpeed = 4000.f;
	MinSpeed = 500.f;
	CurrentForwardSpeed = 500.f;
}


// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	FlyEffect->Deactivate();
	
	Roll = SMesh->GetRelativeRotation().Yaw;
	Pitch = SMesh->GetRelativeRotation().Pitch;
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind our control axis' to callback functions
	PlayerInputComponent->BindAxis("Thrust", this, &ASCharacter::Thrust);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction(TEXT("PrimaryAttack"), IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction(TEXT("PrimaryAttack"), IE_Pressed, this, &ASCharacter::PrimaryAttackPowerUp);
	PlayerInputComponent->BindAction(TEXT("PrimaryInteraction"), IE_Pressed, this, &ASCharacter::PrimaryInteraction);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &ASCharacter::SprintStart);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &ASCharacter::sprintStop);

}

// Move Ship Forwards/Backwards
void ASCharacter::Thrust(float Val)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Roll = 0.0f;
	
	AddMovementInput(ControlRot.Vector(), Val);
}


// Move Ship to the Right/Left
void ASCharacter::MoveRight(float Val)
{
	float TargetYawSpeed = (Val * TurnSpeed);

	// Smoothly interpolate to target yaw speed
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
	
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector, Val);

	FRotator RelativeRotation = SMesh->GetRelativeRotation();
	RelativeRotation.Pitch = (CurrentYawSpeed/TurnSpeed) * 45;
	
	SMesh->SetRelativeRotation(FRotator(-(RelativeRotation.Pitch),SMesh->GetRelativeRotation().Yaw,SMesh->GetRelativeRotation().Roll));
	
}

void ASCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, TEXT("Sprint"));
}

void ASCharacter::sprintStop()
{
	ActionComp->StopActionByName(this, TEXT("Sprint"));
}

void ASCharacter::PrimaryInteraction()
{
	InteractionComp->PrimaryInteraction();
}

FVector ASCharacter::GetPawnViewLocation() const
{
	return CamaraComp->GetComponentLocation();
}

void ASCharacter::PrimaryAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Character: %s"), *GetNameSafe(this));
	ActionComp->StartActionByName(this, "PrimaryAttack");
}

void ASCharacter::PrimaryAttackPowerUp()
{
	ActionComp->StartActionByName(this, "PrimaryAttackPowerUp");
}

void ASCharacter::OnHealtChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.0f && Delta > 0.f)
	{
		SetLifeSpan(0.5f);
	}
}

void ASCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASCharacter, SMesh);
}
