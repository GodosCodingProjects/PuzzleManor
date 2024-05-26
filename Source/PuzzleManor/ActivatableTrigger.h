// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trigger.h"
#include "Activatable.h"

#include "ActivatableTrigger.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PUZZLEMANOR_API UActivatableTrigger : public UTrigger, public IActivatable
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void StartActivation() override;
	
public:
	UPROPERTY(EditAnywhere)
	float Delay = 1.0f;

	bool IsActivated = false;
	float Timer = 0.0f;
};
