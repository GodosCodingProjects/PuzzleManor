// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerWidget.h"
#include "ClickableWidget.h"
#include "MouseFollowWidget.h"

#include "WComputer1_Alt.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMANOR_API UWComputer1_Alt : public UTriggerWidget
{
	GENERATED_BODY()
	
protected:
	virtual void OnWidgetRebuilt() override;

	// Must be overriden
	virtual bool CheckAnswer() override;

private:
	UFUNCTION()
	void OnColorClicked(UClickableWidget* CallingWidget, const FGeometry& CallingGeometry);

	void GrabColor(UClickableWidget* CallingWidget);
	void DropColor();

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UClickableWidget* Color1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UClickableWidget* Color2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UClickableWidget* Color3;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UClickableWidget* Color4;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUserWidget* MouseCursor;

private:
	const TArray<FLinearColor> ExpectedAnswer
	{
		FLinearColor(0.317647f, 1.0f, 0.223529f, 1.0f), // Green
		FLinearColor(1.0f, 0.952941f, 0.0f, 1.0f),		// Yellow
		FLinearColor(0.0f, 0.0f, 1.0f, 1.0f),			// Blue
		FLinearColor(1.0f, 0.352941f, 0.05098f, 1.0f),	// Orange
	};

	UClickableWidget* CurrSelected = nullptr;
	FLinearColor CurrSelectedColor;
};
