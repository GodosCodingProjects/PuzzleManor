// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableAudio.h"

UActivatableAudio::UActivatableAudio()
{
	bAutoActivate = false;
}

void UActivatableAudio::StartActivation()
{
	if (IsStoppable && IsPlaying())
	{
		Stop();
	}
	else
	{
		Play();
	}
}
