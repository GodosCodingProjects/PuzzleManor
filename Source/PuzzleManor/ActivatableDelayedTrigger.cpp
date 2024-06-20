// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableDelayedTrigger.h"

void UActivatableDelayedTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsActivated)
	{
		Timer += DeltaTime;
		if (Timer >= Delay)
		{
			Trigger();
			IsActivated = false;
		}
	}
}

void UActivatableDelayedTrigger::StartActivation()
{
	if (!IsActivated)
	{
		IsActivated = true;
		Timer = 0.0f;
	}
}
