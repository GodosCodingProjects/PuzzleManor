// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableTrigger.h"

void UActivatableTrigger::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);
}

void UActivatableTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Timer += DeltaTime;
	if (Timer >= Delay)
	{
		SetComponentTickEnabled(false);

		Trigger();
	}
}

void UActivatableTrigger::StartActivation()
{
	if (!IsActivated)
	{
		IsActivated = true;
		SetComponentTickEnabled(true);
	}
}
