// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleManorCharacter.h"

// Sets default values
APuzzleManorCharacter::APuzzleManorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APuzzleManorCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APuzzleManorCharacter::MoveFB(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value * MoveSpeed);
}

void APuzzleManorCharacter::MoveRL(float Value)
{
	AddMovementInput(GetActorRightVector(), Value * MoveSpeed);
}

void APuzzleManorCharacter::Rotate(float Value)
{
	AddControllerYawInput(Value * RotSpeed);
}

void APuzzleManorCharacter::Pitch(float Value)
{
	Camera->AddRelativeRotation(FRotator(Value * PitchSpeed, 0.0f, 0.0f));
	Camera->SetRelativeRotation(FRotator
	(
		FMath::Clamp(Camera->GetRelativeRotation().Pitch,MinPitchAngle, MaxPitchAngle),
		0.0f,
		0.0f)
	);
}

void APuzzleManorCharacter::Interact(FKey key)
{
	if (ViewedActor)
	{
		auto Trigger = ViewedActor->FindComponentByClass<UClickTrigger>();
		if (Trigger)
		{
			Trigger->Trigger();
		}
	}
}

void APuzzleManorCharacter::UpdateView()
{
	FHitResult hit;
	GetWorld()->LineTraceSingleByChannel
	(
		hit, 
		Camera->GetComponentLocation(), 
		Camera->GetComponentLocation() + Camera->GetForwardVector() * MaxThoughtRange,
		ECollisionChannel::ECC_Visibility
	);

	if (hit.IsValidBlockingHit())
	{
		ViewedActor = hit.GetActor();
	}
	else
	{
		ViewedActor = nullptr;
	}
}

// Called every frame
void APuzzleManorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateView();
}

// Called to bind functionality to input
void APuzzleManorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &APuzzleManorCharacter::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveRL"), this, &APuzzleManorCharacter::MoveRL);
	PlayerInputComponent->BindAxis(TEXT("Rotate"), this, &APuzzleManorCharacter::Rotate);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &APuzzleManorCharacter::Pitch);
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &APuzzleManorCharacter::Interact);
}

