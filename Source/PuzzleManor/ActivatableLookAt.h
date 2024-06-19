// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Activatable.h"
#include "PuzzleManorCharacter.h"
#include "Camera/CameraComponent.h"

#include "ActivatableLookAt.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEMANOR_API UActivatableLookAt : public USceneComponent, public IActivatable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActivatableLookAt();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void StartActivation() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float ViewTime = 1.0f;
	float ViewTimer = 0.0f;
	float StopViewTimer = 0.0f;

	UPROPERTY(EditAnywhere)
	float AnimationTime = 2.0f;
	float AnimationTimer = 0.0f;

	bool IsActivated = false;

	APuzzleManorCharacter* Player;
	UCameraComponent* Camera;
	FRotator DesiredRotation;
	FRotator InitialRotation;
};
