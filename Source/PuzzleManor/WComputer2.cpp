// Fill out your copyright notice in the Description page of Project Settings.


#include "WComputer2.h"

bool UWComputer2::CheckAnswer()
{
	if (AnswerText)
	{
		return FText::TrimPrecedingAndTrailing(AnswerText->Text).EqualTo(FText::FromString("16"));
	}
	return false;
}
