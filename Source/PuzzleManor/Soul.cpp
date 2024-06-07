
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

	Lookable = FindComponentByClass<ULookable>();
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
				IdentifySoul();
				StartMove(WaitingPosition);
			}
			else if (DesiredPosition != WaitingPosition)
			{
				KillPlayer();
			}
			break;

		case Good:
			if (DesiredPosition == AnubisPosition)
			{
				SetCompleted();
			}
			else if (DesiredPosition != WaitingPosition)
			{
				KillPlayer();
			}
			break;

		case Bad:
			if (DesiredPosition == AmmitPosition)
			{
				SetCompleted();
			}
			else if (DesiredPosition != WaitingPosition)
			{
				KillPlayer();
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

	StartMove(WaitingPosition);
}

void ASoul::OnInteract(AActor* ViewedActor, FVector ViewIntersection)
{
	if (State != Complete && GetActorLocation().Equals(DesiredPosition, TOLERANCE))
	{
		if (ViewedActor == Osiris && State == Unknown)
		{
			StartMove(OsirisPosition);
		}
		else if (ViewedActor == Anubis)
		{
			StartMove(AnubisPosition);
		}
		else if (ViewedActor == Ammit)
		{
			StartMove(AmmitPosition);
		}
	}
}

void ASoul::StartMove(FVector MoveTo)
{
	SetActorTickEnabled(true);
	DesiredPosition = MoveTo;
}

void ASoul::IdentifySoul()
{
	State = (SoulState)FMath::RandRange(1, 2);

	auto NS = FindComponentByClass<UNiagaraComponent>();
	NS->SetColorParameter(
		FName("CurrentColor"),
		(State == Good) ? FLinearColor(0.f, 0.f, 1.f) : FLinearColor(1.f, 0.f, 0.f)
	);

	Lookable->Thoughts = (State == Good) ? 
		"A Soul. It weighs no more than a feather. It has led a good life." : 
		"A Soul. It weighs more than a feather. It has led a sinful life."
	;
}

void ASoul::KillPlayer()
{
	auto Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto CurrentWidget = CreateWidget<UWDead>(Player, DeadWidgetClass);

	FInputModeGameAndUI Mode;
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	Mode.SetHideCursorDuringCapture(false);
	Mode.SetWidgetToFocus(CurrentWidget->GetCachedWidget());

	Player->SetInputMode(Mode);
	Player->bShowMouseCursor = true;

	CurrentWidget->AddToViewport(2);

	Cast<APuzzleManorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->SetInputEnabled(false);
}

void ASoul::SetCompleted()
{
	State = Complete;
	auto Components = CompleteActivatable->GetComponentsByInterface(UActivatable::StaticClass());
	for (auto Component : Components) {
		auto Activatable = Cast<IActivatable>(Component);
		if (Activatable)
		{
			Activatable->StartActivation();
		}
	}
}

FVector ASoul::ExpDecay(FVector a, FVector b, float decay, float dt)
{
	return b + (a - b) * exp(-decay * dt);
}
