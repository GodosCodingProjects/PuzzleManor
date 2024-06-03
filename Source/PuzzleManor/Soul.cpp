
// Fill out your copyright notice in the Description page of Project Settings.


#include "Soul.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleManorCharacter.h"

// Sets default values
ASoul::ASoul()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASoul::BeginPlay()
{
	Super::BeginPlay();
	DesiredPosition = GetActorLocation();
	SetActorTickEnabled(false);
}

// Called every frame
void ASoul::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(ExpDecay(GetActorLocation(), DesiredPosition, Decay, DeltaTime));

	if (GetActorLocation().Equals(DesiredPosition, TOLERANCE))
	{
		SetActorTickEnabled(false);

		switch (State) {
		case Unknown:
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Unknown State"));
			if (DesiredPosition == OsirisPosition)
			{
				SetActorTickEnabled(true);
				DesiredPosition = WaitingPosition;
				// TODO: Randomize a new state for the soul (and update color)
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Randomizing the soul's state"));
				State = Good;
			}
			else if (DesiredPosition != WaitingPosition)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("DEAD"));
			}
			break;

		case Good:
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Good State"));
			if (DesiredPosition == AnubisPosition)
			{
				// TODO: Activate stuff
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Soul was good"));
			}
			else if (DesiredPosition != WaitingPosition)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("DEAD"));
			}
			break;

		case Bad:
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Bad State"));
			if (DesiredPosition == AmmitPosition)
			{
				// TODO: Activate stuff
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Soul was bad"));
			}
			else if (DesiredPosition != WaitingPosition)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("DEAD"));
			}
		}
	}
}

void ASoul::StartActivation()
{
	auto Player = Cast<APuzzleManorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		Player->OnInteract.AddUniqueDynamic(this, &ASoul::OnInteract);
	}
	

	SetActorTickEnabled(true);
	DesiredPosition = WaitingPosition;
}

void ASoul::OnInteract(AActor* ViewedActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("State: " + FString::FromInt(State)));

	if (State != Complete && GetActorLocation().Equals(DesiredPosition, TOLERANCE))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Ready"));

		if (ViewedActor == Osiris)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Osiris"));
			// TODO: Move the soul to osiris position
			SetActorTickEnabled(true);
			DesiredPosition = OsirisPosition;
		}
		else if (ViewedActor == Anubis)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Anubis"));
			// TODO: Move the soul to anubis position
			SetActorTickEnabled(true);
			DesiredPosition = AnubisPosition;
		}
		else if (ViewedActor == Ammit)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Ammit"));
			// TODO: Move the soul to Ammit position
			SetActorTickEnabled(true);
			DesiredPosition = AmmitPosition;
		}
	}
}

FVector ASoul::ExpDecay(FVector a, FVector b, float decay, float dt)
{
	return b + (a - b) * exp(-decay * dt);
}
