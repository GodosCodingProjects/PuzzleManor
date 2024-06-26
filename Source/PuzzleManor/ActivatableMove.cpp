// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableMove.h"

// Sets default values for this component's properties
UActivatableMove::UActivatableMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UActivatableMove::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);

	if (AnimationTime > 0.0)
	{
		TranslationSpeed = Translation / AnimationTime;
		RotationSpeed = Rotation * (1.0f / AnimationTime);
	}
}


// Called every frame
void UActivatableMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float ClampedDelta = FMath::Min(DeltaTime, AnimationTime - AnimationTimer);

	if (AnimationTime > 0.0)
	{
		GetOwner()->AddActorWorldOffset(TranslationSpeed * ClampedDelta);
		GetOwner()->AddActorWorldRotation(RotationSpeed * ClampedDelta);
	}
	else
	{
		GetOwner()->AddActorWorldOffset(Translation);
		GetOwner()->AddActorWorldRotation(Rotation);
	}

	AnimationTimer += DeltaTime;
	if (AnimationTimer >= AnimationTime)
	{
		SetComponentTickEnabled(false);
		IsActivated = false;
	}
}

void UActivatableMove::StartActivation()
{
	if (!IsActivated)
	{
		AnimationTimer = 0.0f;
		IsActivated = true;
		SetComponentTickEnabled(true);
	}
}

