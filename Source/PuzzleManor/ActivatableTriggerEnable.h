// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Activatable.h"
#include "Trigger.h"

#include "ActivatableTriggerEnable.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEMANOR_API UActivatableTriggerEnable : public UActorComponent, public IActivatable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActivatableTriggerEnable();

	virtual void StartActivation() override;
		
public:
	UPROPERTY(EditAnywhere)
	AActor* TriggerToEnableActor;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTrigger> TriggerToEnableClass;
};
