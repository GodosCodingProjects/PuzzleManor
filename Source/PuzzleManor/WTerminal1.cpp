// Fill out your copyright notice in the Description page of Project Settings.


#include "WTerminal1.h"

bool UWTerminal1::CheckAnswer()
{
	if (AnswerBox)
	{
		return AnswerBox->Value == 69;
	}
	return false;
}
