// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "WMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMANOR_API UWMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void OnWidgetRebuilt() override;

	UFUNCTION()
	void OnResume();

	UFUNCTION()
	void OnRestart();

	UFUNCTION()
	void OnQuit();

private:
	void Close();
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* QuitButton;
};
