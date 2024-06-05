// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"



UTrigger::UTrigger()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTrigger::Trigger()
{
	if (IsEnabled && TimeSinceLastTrigger >= TriggerCooldown)
	{
		for (auto ActivatableActor : ActivatableActors)
		{
			auto Components = ActivatableActor->GetComponentsByInterface(UActivatable::StaticClass());

			for (auto Component : Components) {
				auto Activatable = Cast<IActivatable>(Component);
				if (Activatable)
				{
					Activatable->StartActivation();
				}
			}

			if (ActivatableActor->Implements<UActivatable>()) {
				Cast<IActivatable>(ActivatableActor)->StartActivation();
			}
		}

		IsEnabled = CanRetrigger;

		if (CanRetrigger)
		{
			TimeSinceLastTrigger = 0.0f;
		}
	}
}

void UTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastTrigger += DeltaTime;
}
