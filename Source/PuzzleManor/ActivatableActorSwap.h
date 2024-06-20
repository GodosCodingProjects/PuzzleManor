// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Activatable.h"

#include "ActivatableActorSwap.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEMANOR_API UActivatableActorSwap : public UActorComponent, public IActivatable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActivatableActorSwap();

	virtual void StartActivation() override;

public:
	UPROPERTY(EditAnywhere)
	AActor* SwapTarget;
};
