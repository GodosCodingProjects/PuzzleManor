// Fill out your copyright notice in the Description page of Project Settings.


#include "FenceTrigger.h"
#include "NiagaraComponent.h"
#include "ActivatableCountTrigger.h"

void UFenceTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	size_t nLitFires = 0;
	for (size_t i = 0; i < Candles.Num(); ++i)
	{
		auto NS = Flames[i]->FindComponentByClass<UNiagaraComponent>();
		auto RotCount = Candles[i]->FindComponentByClass<UActivatableCountTrigger>()->Counter;

		if (RotCount % 4 == ExpectedCandleRotations[i])
		{
			++nLitFires;
			if (!NS->IsActive())
			{
				NS->Activate();
			}
		}
		else
		{
			if (NS->IsActive())
			{
				NS->Deactivate();
			}
		}
	}

	if (nLitFires > LastCorrectAmount)
	{
		AddFlameSound->StartActivation();
	}
	else if (nLitFires < LastCorrectAmount)
	{
		RemoveFlameSound->StartActivation();
	}

	LastCorrectAmount = nLitFires;

	if (nLitFires == 6)
	{
		Trigger();
	}
}

void UFenceTrigger::BeginPlay()
{
	auto Audios = SoundActor->GetComponents();

	for (auto Audio : Audios)
	{
		if (Audio->GetName() == "AddFlameAudio")
		{
			AddFlameSound = Cast<UActivatableAudio>(Audio);
		}
		else if (Audio->GetName() == "RemoveFlameAudio")
		{
			RemoveFlameSound = Cast<UActivatableAudio>(Audio);
		}
	}
}
