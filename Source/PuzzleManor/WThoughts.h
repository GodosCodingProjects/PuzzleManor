// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "WThoughts.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PUZZLEMANOR_API UWThoughts : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetText();

public:
	UPROPERTY(EditAnywhere,	meta = (BindWidget))
	UTextBlock* Text;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Background;
};
