// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "TriggerWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMANOR_API UTriggerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void OnWidgetRebuilt() override;

	UFUNCTION()
	void OnSubmit();

	UFUNCTION()
	void OnClose();

protected:
	// Must be overriden
	virtual bool CheckAnswer() { return true; }

	virtual void Disable();

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* SubmitButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* XButton;

	TArray<AActor*> ActivatableActors;

	bool IsSolved = false;
};
