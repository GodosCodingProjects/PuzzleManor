// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapPin.generated.h"

UCLASS()
class PUZZLEMANOR_API AMapPin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapPin();

	UFUNCTION()
	void OnInteract(AActor* ViewedActor, FVector ViewIntersection);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	AActor* Pin;
};
