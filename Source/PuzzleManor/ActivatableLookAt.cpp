// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableLookAt.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UActivatableLookAt::UActivatableLookAt()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UActivatableLookAt::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsActivated)
	{
		if (ViewTimer < ViewTime)
		{
			ViewTimer += DeltaTime;
			double RotFraction = FMath::Clamp(ViewTimer / ViewTime, 0.0, 1.0);
			Camera->SetWorldRotation(FMath::Lerp(InitialRotation, DesiredRotation, RotFraction));
		}
		else if (AnimationTimer < AnimationTime)
		{
			AnimationTimer += DeltaTime;
		}
		else if (StopViewTimer < ViewTime)
		{
			StopViewTimer += DeltaTime;
			double RotFraction = FMath::Clamp(StopViewTimer / ViewTime, 0.0, 1.0);
			Camera->SetWorldRotation(FMath::Lerp(DesiredRotation, InitialRotation, RotFraction));
		}
		else
		{
			IsActivated = false;
			Player->SetInputEnabled(true);
		}
	}
}

void UActivatableLookAt::StartActivation()
{
	if (!IsActivated)
	{
		IsActivated = true;
		Player->SetInputEnabled(false);

		InitialRotation = Camera->GetComponentRotation();

		DesiredRotation = UKismetMathLibrary::FindLookAtRotation(
			Camera->GetComponentLocation(),
			GetComponentLocation()
		);

		ViewTimer = 0.0;
		StopViewTimer = 0.0;
		AnimationTimer = 0.0;
	}
}

void UActivatableLookAt::BeginPlay()
{
	Player = Cast<APuzzleManorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Camera = Player->Camera;
}

