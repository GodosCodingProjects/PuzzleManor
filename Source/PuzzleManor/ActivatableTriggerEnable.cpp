// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableTriggerEnable.h"

// Sets default values for this component's properties
UActivatableTriggerEnable::UActivatableTriggerEnable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UActivatableTriggerEnable::StartActivation()
{
	if (TriggerToEnableActor)
	{
		auto TriggerToEnable = Cast<UTrigger>(TriggerToEnableActor->
			FindComponentByClass(TriggerToEnableClass.GetDefaultObject()->StaticClass()));

		if (TriggerToEnable)
		{
			TriggerToEnable->IsEnabled = true;
		}
	}
}
