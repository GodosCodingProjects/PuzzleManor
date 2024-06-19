// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "WBadEnd.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMANOR_API UWBadEnd : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void OnWidgetRebuilt() override;

	UFUNCTION()
	void OnRestart();

	UFUNCTION()
	void OnQuit();

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* QuitButton;
};
