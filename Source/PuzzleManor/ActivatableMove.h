// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Activatable.h"

#include "ActivatableMove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEMANOR_API UActivatableMove : public UActorComponent, public IActivatable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActivatableMove();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void StartActivation() override;

public:
	UPROPERTY(EditAnywhere)
	FVector Translation;

	UPROPERTY(EditAnywhere)
	FRotator Rotation;
	
	UPROPERTY(EditAnywhere)
	float AnimationTime = 1.0f;

private:
	bool IsActivated = false;

	FVector TranslationSpeed;
	FRotator RotationSpeed;
	float AnimationTimer = 0.0f;
};
