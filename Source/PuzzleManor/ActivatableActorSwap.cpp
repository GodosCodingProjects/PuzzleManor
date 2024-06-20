// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableActorSwap.h"

// Sets default values for this component's properties
UActivatableActorSwap::UActivatableActorSwap()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UActivatableActorSwap::StartActivation()
{
	if (SwapTarget)
	{
		auto tmp = GetOwner()->GetActorTransform();

		GetOwner()->SetActorTransform(SwapTarget->GetActorTransform());
		SwapTarget->SetActorTransform(tmp);
	}
}
