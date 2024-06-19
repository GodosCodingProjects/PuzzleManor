// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "WMenu.h"

#include "PuzzleManorCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActorEventSignature, AActor*, ViewedActor, FVector, ViewIntersection);

UCLASS()
class PUZZLEMANOR_API APuzzleManorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APuzzleManorCharacter();

	void SetInputEnabled(bool SetEnabled);

protected:
	virtual void BeginPlay() override;

	void MoveFB(float Value);
	void MoveRL(float Value);
	void Rotate(float Value);
	void Pitch(float Value);
	void Interact(FKey key);
	void OpenMenu();

	void UpdateView();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	AActor* ViewedActor = nullptr;
	FVector ViewIntersection;

	FActorEventSignature OnInteract;
	FActorEventSignature OnViewStart;
	FActorEventSignature OnViewEnd;

public:
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

private:
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 10.0f;

	UPROPERTY(EditAnywhere)
	float RotSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	float MaxThoughtRange = 500.0f;

	UPROPERTY(EditAnywhere)
	float MaxPitchAngle = 45.0f;

	UPROPERTY(EditAnywhere)
	float MinPitchAngle = -55.0f;

	UPROPERTY(EditAnywhere)
	float PitchSpeed = 3.0f;

	bool IsEnabled = true;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWMenu> MenuClass;

	UAudioComponent* LeftStep;
	UAudioComponent* RightStep;

	UPROPERTY(EditAnywhere)
	float StepDelay = 0.5f;
	float StepCounter = 0.0f;
	bool IsNextStepLeft = true;
};
