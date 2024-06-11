// Fill out your copyright notice in the Description page of Project Settings.


#include "WComputer1_Alt.h"
#include "Kismet/GameplayStatics.h"
#include "Components/HorizontalBoxSlot.h"

void UWComputer1_Alt::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	Color1->OnClickCompleted.AddUniqueDynamic(this, &UWComputer1_Alt::OnColorClicked);
	Color2->OnClickCompleted.AddUniqueDynamic(this, &UWComputer1_Alt::OnColorClicked);
	Color3->OnClickCompleted.AddUniqueDynamic(this, &UWComputer1_Alt::OnColorClicked);
	Color4->OnClickCompleted.AddUniqueDynamic(this, &UWComputer1_Alt::OnColorClicked);
}

bool UWComputer1_Alt::CheckAnswer()
{
	if (!Color1->GetColorAndOpacity().Equals(ExpectedAnswer[0]))
	{
		return false;
	}
	
	if (!Color2->GetColorAndOpacity().Equals(ExpectedAnswer[1]))
	{
		return false;
	}

	if (!Color3->GetColorAndOpacity().Equals(ExpectedAnswer[2]))
	{
		return false;
	}

	return Color4->GetColorAndOpacity().Equals(ExpectedAnswer[3]);
}

void UWComputer1_Alt::OnColorClicked(UClickableWidget* CallingWidget, const FGeometry& CallingGeometry)
{
	if (CurrSelected == CallingWidget)
	{
		CurrSelected->SetColorAndOpacity(CurrSelectedColor);
		DropColor();
	}
	else
	{
		if (CurrSelected == nullptr)
		{
			GrabColor(CallingWidget);
		}
		else
		{
			CurrSelected->SetColorAndOpacity(CallingWidget->GetColorAndOpacity());
			CallingWidget->SetColorAndOpacity(CurrSelectedColor);

			DropColor();
		}
	}
}

void UWComputer1_Alt::GrabColor(UClickableWidget* CallingWidget)
{
	CurrSelected = CallingWidget;
	CurrSelectedColor = CurrSelected->GetColorAndOpacity();
	CurrSelected->SetColorAndOpacity(FColor::White);

	MouseCursor->SetColorAndOpacity(CurrSelectedColor);
	auto Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Player->SetMouseCursorWidget(EMouseCursor::Custom, MouseCursor);
	Player->CurrentMouseCursor = EMouseCursor::Custom;
}

void UWComputer1_Alt::DropColor()
{
	CurrSelected = nullptr;

	auto Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Player->CurrentMouseCursor = Player->DefaultMouseCursor;
}
