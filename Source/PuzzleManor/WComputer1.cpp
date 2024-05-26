// Fill out your copyright notice in the Description page of Project Settings.


#include "WComputer1.h"
#include "Kismet/GameplayStatics.h"

bool UWComputer1::CheckAnswer()
{
	auto Children = Grid->GetAllChildren();
	size_t i = 0;

	for (auto Child : Children)
	{
		auto CheckBox = Cast<UCheckBox>(Child);

		if (CheckBox)
		{
			if (CheckBox->CheckedState != Answer[i])
			{
				return false;
			}

			++i;
		}
	}

	if (i == 16)
	{
		return true;
	}
	
	return false;
}
