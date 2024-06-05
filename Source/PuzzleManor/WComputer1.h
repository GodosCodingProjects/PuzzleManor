// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerWidget.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Components/CheckBox.h"

#include "WComputer1.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMANOR_API UWComputer1 : public UTriggerWidget
{
	GENERATED_BODY()

protected:
	// Must be overriden
	virtual bool CheckAnswer() override;
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUniformGridPanel* Grid;

private:
	const ECheckBoxState Answer[16] = {
		ECheckBoxState::Unchecked, ECheckBoxState::Checked, ECheckBoxState::Unchecked, ECheckBoxState::Unchecked,
		ECheckBoxState::Unchecked, ECheckBoxState::Unchecked, ECheckBoxState::Checked, ECheckBoxState::Unchecked,
		ECheckBoxState::Checked, ECheckBoxState::Unchecked, ECheckBoxState::Unchecked, ECheckBoxState::Unchecked,
		ECheckBoxState::Unchecked, ECheckBoxState::Unchecked, ECheckBoxState::Unchecked, ECheckBoxState::Checked,
	};
};
