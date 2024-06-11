// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"

#include "ClickableWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FClickedWidgetSignature, UClickableWidget*, CallingWidget, const FGeometry&, CallingGeometry);

/**
 * 
 */
UCLASS()
class PUZZLEMANOR_API UClickableWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FClickedWidgetSignature OnClickCompleted;
	
protected:
	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* WidgetImage;
};
