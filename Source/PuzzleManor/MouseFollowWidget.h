// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"

#include "MouseFollowWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMANOR_API UMouseFollowWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	bool IsFollowing = true;

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* WidgetImage;
};
