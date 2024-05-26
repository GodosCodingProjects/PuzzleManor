// Fill out your copyright notice in the Description page of Project Settings.


#include "WThoughts.h"

#include "PuzzleManorCharacter.h"
#include "Lookable.h"
#include "Kismet/GameplayStatics.h"


void UWThoughts::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	UUserWidget::NativeTick(MyGeometry, InDeltaTime);

	SetText();
}

void UWThoughts::SetText()
{
	bool HasText = false;

	auto Player = Cast<APuzzleManorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player && Player->ViewedActor)
	{
		auto Lookable = Player->ViewedActor->FindComponentByClass<ULookable>();

		if (Lookable && !Lookable->Thoughts.IsEmpty())
		{
			HasText = true;

			Text->SetText(FText::FromString(Lookable->Thoughts));
			Background->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.4f));
		}
	}

	if (!HasText)
	{
		Text->SetText(FText::FromString(""));
		Background->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
	}
}
