// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Lookable.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEMANOR_API ULookable : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULookable();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Thoughts = "";
};
