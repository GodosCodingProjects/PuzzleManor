// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerWidget.h"
#include "Components/SpinBox.h"

#include "WTerminal1.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMANOR_API UWTerminal1 : public UTriggerWidget
{
	GENERATED_BODY()
	
public:
	virtual bool CheckAnswer() override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USpinBox* AnswerBox;
};
