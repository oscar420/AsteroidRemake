// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

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
	PlayerInputComponent->BindAxis("MoveUp", this, &ASCharacter::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent-> BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);

}

// Move Ship Forwards/Backwards
void ASCharacter::Thrust(float Val)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Roll = 0.0f;
	
	AddMovementInput(ControlRot.Vector(), Val);
}


void ASCharacter::MoveUp(float Val)
{
	FRotator Rotation = SMesh->GetRelativeRotation();
	Rotation.Pitch = 0.0f;
	Rotation.Yaw = 0.0f;
	

	AddMovementInput(Rotation.Vector() * 50, Val);
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

	UE_LOG(LogTemp, Warning, TEXT("Current Yaw Speed: %f"), RelativeRotation.Pitch);
	SMesh->SetRelativeRotation(FRotator(-(RelativeRotation.Pitch),SMesh->GetRelativeRotation().Yaw,SMesh->GetRelativeRotation().Roll));
	
}