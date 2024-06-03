
// Fill out your copyright notice in the Description page of Project Settings.


#include "Soul.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleManorCharacter.h"
#include "NiagaraComponent.h"

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
			if (DesiredPosition == OsirisPosition)
			{
				SetActorTickEnabled(true);
				DesiredPosition = WaitingPosition;

				State = (SoulState)FMath::RandRange(1, 2);

				auto NS = FindComponentByClass<UNiagaraComponent>();
				NS->SetColorParameter(
					FName("CurrentColor"),
					(State == Good)? FLinearColor(0.f, 0.f, 1.f) : FLinearColor(1.f, 0.f, 0.f)
				);
			}
			else if (DesiredPosition != WaitingPosition)
			{
				// TODO: Kill the player
				UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("ManorLevel")));
			}
			break;

		case Good:
			if (DesiredPosition == AnubisPosition)
			{
				// TODO: Activate stuff
				State = Complete;
			}
			else if (DesiredPosition != WaitingPosition)
			{
				// TODO: Kill the player
				UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("ManorLevel")));
			}
			break;

		case Bad:
			if (DesiredPosition == AmmitPosition)
			{
				// TODO: Activate stuff
				State = Complete;
			}
			else if (DesiredPosition != WaitingPosition)
			{
				// TODO: Kill the player
				UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("ManorLevel")));
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
	if (State != Complete && GetActorLocation().Equals(DesiredPosition, TOLERANCE))
	{
		if (ViewedActor == Osiris && State == Unknown)
		{
			SetActorTickEnabled(true);
			DesiredPosition = OsirisPosition;
		}
		else if (ViewedActor == Anubis)
		{
			SetActorTickEnabled(true);
			DesiredPosition = AnubisPosition;
		}
		else if (ViewedActor == Ammit)
		{
			SetActorTickEnabled(true);
			DesiredPosition = AmmitPosition;
		}
	}
}

FVector ASoul::ExpDecay(FVector a, FVector b, float decay, float dt)
{
	return b + (a - b) * exp(-decay * dt);
}
