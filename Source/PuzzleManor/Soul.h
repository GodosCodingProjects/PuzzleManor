// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Activatable.h"
#include "Lookable.h"
#include "WDead.h"
#include "Components/AudioComponent.h"

#include "Soul.generated.h"

UCLASS()
class PUZZLEMANOR_API ASoul : public AActor, public IActivatable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoul();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void StartActivation() override;

	UFUNCTION()
	void OnInteract(AActor* ViewedActor, FVector ViewIntersection);

private:
	void StartMove(FVector MoveTo);

	void IdentifySoul();

	void KillPlayer();

	void SetCompleted();

	FVector ExpDecay(FVector a, FVector b, float decay, float dt);

public:
	UPROPERTY(EditAnywhere)
	FVector WaitingPosition;

	UPROPERTY(EditAnywhere)
	FVector OsirisPosition;

	UPROPERTY(EditAnywhere)
	AActor* Osiris;

	UPROPERTY(EditAnywhere)
	FVector AnubisPosition;

	UPROPERTY(EditAnywhere)
	AActor* Anubis;

	UPROPERTY(EditAnywhere)
	FVector AmmitPosition;

	UPROPERTY(EditAnywhere)
	AActor* Ammit;

	UPROPERTY(EditAnywhere)
	float Decay = 16;

	UPROPERTY(EditAnywhere)
	AActor* CompleteActivatable;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWDead> DeadWidgetClass;

private:
	enum SoulState {
		Unknown,
		Good,
		Bad,
		Complete
	} State = Unknown;

	FVector DesiredPosition;

	float TOLERANCE = 1.0f;

	ULookable* Lookable;

	UAudioComponent* RevealAudio;
	UAudioComponent* SuccessAudio;
	UAudioComponent* FailAudio;
};
