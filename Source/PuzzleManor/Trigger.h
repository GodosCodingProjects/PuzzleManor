// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Activatable.h"

#include "Trigger.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEMANOR_API UTrigger : public UActorComponent
{
	GENERATED_BODY()

public:
	UTrigger();

	void Trigger();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere)
	TArray<AActor*> ActivatableActors;

	UPROPERTY(EditAnywhere)
	bool IsEnabled = true;

	UPROPERTY(EditAnywhere)
	bool CanRetrigger = false;

	UPROPERTY(EditAnywhere)
	float TriggerCooldown = 0.0f;

private:
	float TimeSinceLastTrigger = 0.0f;
	bool IsTriggerReady = true;
};
