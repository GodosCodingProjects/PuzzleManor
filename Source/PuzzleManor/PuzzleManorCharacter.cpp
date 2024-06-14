// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleManorCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APuzzleManorCharacter::APuzzleManorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
}

void APuzzleManorCharacter::SetInputEnabled(bool SetEnabled)
{
	IsEnabled = SetEnabled;
}

void APuzzleManorCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto Audios = GetComponents();

	for (auto Audio : Audios)
	{
		if (Audio->GetName() == "LeftStep")
		{
			LeftStep = Cast<UAudioComponent>(Audio);
		}
		else if (Audio->GetName() == "RightStep")
		{
			RightStep = Cast<UAudioComponent>(Audio);
		}
	}
}

void APuzzleManorCharacter::MoveFB(float Value)
{
	if (!IsEnabled)
	{
		return;
	}

	AddMovementInput(GetActorForwardVector(), Value * MoveSpeed);
}

void APuzzleManorCharacter::MoveRL(float Value)
{
	if (!IsEnabled)
	{
		return;
	}

	AddMovementInput(GetActorRightVector(), Value * MoveSpeed);
}

void APuzzleManorCharacter::Rotate(float Value)
{
	if (!IsEnabled)
	{
		return;
	}

	AddControllerYawInput(Value * RotSpeed);
}

void APuzzleManorCharacter::Pitch(float Value)
{
	if (!IsEnabled)
	{
		return;
	}

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
	if (!IsEnabled || !ViewedActor)
	{
		return;
	}

	OnInteract.Broadcast(ViewedActor, ViewIntersection);
}

void APuzzleManorCharacter::OpenMenu()
{
	if (!IsEnabled)
	{
		return;
	}

	auto Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto CurrentWidget = CreateWidget<UWMenu>(Player, MenuClass);

	FInputModeGameAndUI Mode;
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	Mode.SetHideCursorDuringCapture(false);
	Mode.SetWidgetToFocus(CurrentWidget->GetCachedWidget());

	Player->SetInputMode(Mode);
	Player->bShowMouseCursor = true;

	CurrentWidget->AddToViewport(2);

	SetInputEnabled(false);
}

void APuzzleManorCharacter::UpdateView()
{
	if (!IsEnabled)
	{
		return;
	}

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
		if (ViewedActor != hit.GetActor())
		{
			ViewedActor = hit.GetActor();
			OnViewStart.Broadcast(ViewedActor, ViewIntersection);
		}

		ViewIntersection = hit.ImpactPoint;
	}
	else
	{
		if (ViewedActor)
		{
			ViewedActor = nullptr;
			OnViewEnd.Broadcast(ViewedActor, ViewIntersection);
		}
	}
}

// Called every frame
void APuzzleManorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateView();

	if (!GetVelocity().IsZero())
	{
		StepCounter += DeltaTime;
		if (StepCounter > StepDelay)
		{
			StepCounter -= StepDelay;

			if (IsNextStepLeft)
			{
				LeftStep->Play();
			}
			else
			{
				RightStep->Play();
			}

			IsNextStepLeft = !IsNextStepLeft;
		}
	}
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
	PlayerInputComponent->BindAction(TEXT("OpenMenu"), EInputEvent::IE_Pressed, this, &APuzzleManorCharacter::OpenMenu);
}

