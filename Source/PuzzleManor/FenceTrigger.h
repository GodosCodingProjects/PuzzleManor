// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trigger.h"
#include "FenceTrigger.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PUZZLEMANOR_API UFenceTrigger : public UTrigger
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:
	UPROPERTY(EditAnywhere)
	TArray<AActor*> Flames;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> Candles;

private:
	TArray<int> ExpectedCandleRotations = {
		3,
		2,
		1,
		2,
		0,
		1
	};
};
