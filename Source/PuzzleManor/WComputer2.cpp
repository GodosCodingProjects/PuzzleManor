// Fill out your copyright notice in the Description page of Project Settings.


#include "WComputer2.h"

bool UWComputer2::CheckAnswer()
{
	if (AnswerBox)
	{
		return AnswerBox->Value == 16;
	}
	return false;
}
