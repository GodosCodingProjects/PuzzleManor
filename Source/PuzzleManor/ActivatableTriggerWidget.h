// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Activatable.h"
#include "TriggerWidget.h"

#include "ActivatableTriggerWidget.generated.h"

USTRUCT()
struct FActivatableActors
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<AActor*> ActivatableActors;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEMANOR_API UActivatableTriggerWidget : public UActorComponent, public IActivatable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActivatableTriggerWidget();

	virtual void StartActivation() override;

public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UTriggerWidget>> WidgetClasses;

	UPROPERTY(EditAnywhere)
	TArray<FActivatableActors> ActivatableActorsList;

private:
	UTriggerWidget* CurrentWidget;
	size_t i;
};
