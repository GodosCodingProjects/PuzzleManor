// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trigger.h"
#include "Activatable.h"

#include "ActivatableCountTrigger.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PUZZLEMANOR_API UActivatableCountTrigger : public UTrigger, public IActivatable
{
	GENERATED_BODY()
	
public:
	virtual void StartActivation() override;

public:
	UPROPERTY(EditAnywhere)
	int CountTo = 1;

private:
	int Counter = 0;
};
