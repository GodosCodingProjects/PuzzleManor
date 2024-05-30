// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableDelayedTrigger.h"

void UActivatableDelayedTrigger::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);
}

void UActivatableDelayedTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Timer += DeltaTime;
	if (Timer >= Delay)
	{
		SetComponentTickEnabled(false);

		Trigger();
	}
}

void UActivatableDelayedTrigger::StartActivation()
{
	if (!IsActivated)
	{
		IsActivated = true;
		SetComponentTickEnabled(true);
	}
}
