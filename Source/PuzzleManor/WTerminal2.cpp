// Fill out your copyright notice in the Description page of Project Settings.


#include "WTerminal2.h"

bool UWTerminal2::CheckAnswer()
{
	if (AnswerText)
	{
		return FText::TrimPrecedingAndTrailing(AnswerText->Text).ToLower().EqualTo(FText::FromString("osiris"));
	}
	return false;
}
