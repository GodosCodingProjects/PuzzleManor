// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableACDestroy.h"

// Sets default values for this component's properties
UActivatableACDestroy::UActivatableACDestroy()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UActivatableACDestroy::StartActivation()
{
	if (Target)
	{
		auto ComponentFound = Target->FindComponentByClass(TargetComponentClass);
		if (ComponentFound)
		{
			ComponentFound->DestroyComponent();
		}
	}
}

