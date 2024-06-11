// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Activatable.h"

#include "ActivatableAudio.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PUZZLEMANOR_API UActivatableAudio : public UAudioComponent, public IActivatable
{
	GENERATED_BODY()
	
public:
	UActivatableAudio();

	void StartActivation() override;
};
