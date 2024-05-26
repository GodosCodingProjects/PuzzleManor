// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableTriggerWidget.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UActivatableTriggerWidget::UActivatableTriggerWidget()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UActivatableTriggerWidget::StartActivation()
{
	if (WidgetClass)
	{
		auto Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (Player)
		{
			if (!WidgetInstance)
			{
				WidgetInstance = CreateWidget<UTriggerWidget>(Player, WidgetClass);
				WidgetInstance->ActivatableActors = ActivatableActors;
			}
			
			if (WidgetInstance)
			{
				FInputModeGameAndUI Mode;
				Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				Mode.SetHideCursorDuringCapture(false);
				Mode.SetWidgetToFocus(WidgetInstance->GetCachedWidget());

				Player->SetInputMode(Mode);
				Player->bShowMouseCursor = true;

				WidgetInstance->AddToViewport(2);
			}
		}
	}
}
