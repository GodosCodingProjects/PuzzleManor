// Fill out your copyright notice in the Description page of Project Settings.


#include "WThoughts.h"

#include "PuzzleManorCharacter.h"
#include "Lookable.h"
#include "Kismet/GameplayStatics.h"


void UWThoughts::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	auto Player = Cast<APuzzleManorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		Player->OnViewEnd.AddUniqueDynamic(this, &UWThoughts::OnViewUpdated);
		Player->OnViewStart.AddUniqueDynamic(this, &UWThoughts::OnViewUpdated);
	}
}

void UWThoughts::OnViewUpdated(AActor* ViewedActor)
{
	bool HasText = false;

	if (ViewedActor)
	{
		auto Lookable = ViewedActor->FindComponentByClass<ULookable>();
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
