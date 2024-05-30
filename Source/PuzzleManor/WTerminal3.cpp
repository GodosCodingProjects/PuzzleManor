// Fill out your copyright notice in the Description page of Project Settings.


#include "WTerminal3.h"

bool UWTerminal3::CheckAnswer()
{
	if (AnswerText)
	{
		return FText::TrimPrecedingAndTrailing(AnswerText->Text).ToLower().EqualTo(FText::FromString("bach"));
	}
	return false;
}
