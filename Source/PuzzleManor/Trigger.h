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

public:
	UPROPERTY(EditAnywhere)
	TArray<AActor*> ActivatableActors;

	UPROPERTY(EditAnywhere)
	bool IsEnabled = true;

	UPROPERTY(EditAnywhere)
	bool CanRetrigger = false;
};
