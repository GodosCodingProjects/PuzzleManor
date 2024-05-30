// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableCountTrigger.h"

void UActivatableCountTrigger::StartActivation()
{
	++Counter;

	if (Counter >= CountTo) {
		Trigger();
	}
}
