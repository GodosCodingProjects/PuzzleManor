// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "WDead.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMANOR_API UWDead : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void OnWidgetRebuilt() override;

	UFUNCTION()
	void OnRestart();

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* RestartButton;
};
