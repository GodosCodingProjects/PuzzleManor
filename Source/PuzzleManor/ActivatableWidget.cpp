// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleManorCharacter.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UActivatableWidget::UActivatableWidget()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UActivatableWidget::StartActivation()
{
	auto Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Player)
	{
		auto CurrentWidget = CreateWidget<UUserWidget>(Player, WidgetClass);

		FInputModeGameAndUI Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		Mode.SetHideCursorDuringCapture(false);
		Mode.SetWidgetToFocus(CurrentWidget->GetCachedWidget());

		Player->SetInputMode(Mode);
		Player->bShowMouseCursor = true;

		Cast<APuzzleManorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->SetInputEnabled(false);

		CurrentWidget->AddToViewport(2);
	}
}
