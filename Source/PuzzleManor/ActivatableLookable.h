// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lookable.h"
#include "Activatable.h"

#include "ActivatableLookable.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PUZZLEMANOR_API UActivatableLookable : public ULookable, public IActivatable
{
	GENERATED_BODY()

public:
	virtual void StartActivation() override;
	
public:
	UPROPERTY(EditAnywhere)
	FString ChangedThoughts = "";
};
