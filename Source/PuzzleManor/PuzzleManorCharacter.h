// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "ClickTrigger.h"

#include "PuzzleManorCharacter.generated.h"

UCLASS()
class PUZZLEMANOR_API APuzzleManorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APuzzleManorCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveFB(float Value);
	void MoveRL(float Value);
	void Rotate(float Value);
	void Pitch(float Value);
	void Interact(FKey key);

	void UpdateView();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(BlueprintReadOnly)
	AActor* ViewedActor = nullptr;

private:
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 10.0f;

	UPROPERTY(EditAnywhere)
	float RotSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	float MaxThoughtRange = 500.0f;

	UPROPERTY(EditAnywhere)
	float MaxPitchAngle = 45.0f;

	UPROPERTY(EditAnywhere)
	float MinPitchAngle = -55.0f;

	UPROPERTY(EditAnywhere)
	float PitchSpeed = 3.0f;;
};
