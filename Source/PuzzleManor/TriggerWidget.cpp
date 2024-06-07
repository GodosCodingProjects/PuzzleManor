// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleManorCharacter.h"
#include "Activatable.h"


void UTriggerWidget::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (SubmitButton && !SubmitButton->OnClicked.IsBound())
	{
		SubmitButton->OnClicked.AddDynamic(this, &UTriggerWidget::OnSubmit);
	}

	if (XButton && !XButton->OnClicked.IsBound())
	{
		XButton->OnClicked.AddDynamic(this, &UTriggerWidget::OnClose);
	}
}

void UTriggerWidget::OnSubmit()
{
	if (CheckAnswer())
	{
		for (auto ActivatableActor : ActivatableActors)
		{
			auto Components = ActivatableActor->GetComponentsByInterface(UActivatable::StaticClass());

			for (auto Component : Components) {
				auto Activatable = Cast<IActivatable>(Component);
				if (Activatable)
				{
					Activatable->StartActivation();
				}
			}
		}

		Disable();
	}
}

void UTriggerWidget::OnClose()
{
	RemoveFromViewport();

	auto Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FInputModeGameOnly GameMode;
	Player->SetInputMode(GameMode);
	FSlateApplication::Get().SetAllUserFocusToGameViewport();
	Player->bShowMouseCursor = false;

	Cast<APuzzleManorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->SetInputEnabled(true);
}

void UTriggerWidget::Disable()
{
	OnClose();

	IsSolved = true;
}
