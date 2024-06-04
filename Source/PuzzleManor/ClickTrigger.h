// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trigger.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleManorCharacter.h"

#include "ClickTrigger.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PUZZLEMANOR_API UClickTrigger : public UTrigger
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

	UFUNCTION()
	void OnInteracted(AActor* ViewedActor, FVector ViewIntersection);
};
