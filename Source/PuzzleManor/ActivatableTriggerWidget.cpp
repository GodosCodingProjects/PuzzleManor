// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableTriggerWidget.h"
#include "GameFramework/PlayerController.h"
#include "PuzzleManorCharacter.h"
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
	auto Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Player)
	{
		if ((!CurrentWidget || CurrentWidget->IsSolved) && i < WidgetClasses.Num())
		{
			CurrentWidget = CreateWidget<UTriggerWidget>(Player, WidgetClasses[i]);
			CurrentWidget->ActivatableActors = ActivatableActorsList[i].ActivatableActors;
			CurrentWidget->SuccessSound = SuccessSound;
			CurrentWidget->FailSound = FailSound;

			++i;
		}
			
		if (CurrentWidget && !CurrentWidget->IsSolved)
		{
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
}

void UActivatableTriggerWidget::BeginPlay()
{
	auto Audios = SoundActor->GetComponents();

	for (auto Audio : Audios)
	{
		if (Audio->GetName() == "SuccessAudio")
		{
			SuccessSound = Cast<UActivatableAudio>(Audio);
		}
		else if (Audio->GetName() == "FailAudio")
		{
			FailSound = Cast<UActivatableAudio>(Audio);
		}
	}
}
