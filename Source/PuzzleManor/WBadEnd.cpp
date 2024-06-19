// Fill out your copyright notice in the Description page of Project Settings.


#include "WBadEnd.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleManorCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

void UWBadEnd::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddUniqueDynamic(this, &UWBadEnd::OnRestart);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddUniqueDynamic(this, &UWBadEnd::OnQuit);
	}
}

void UWBadEnd::OnRestart()
{
	RemoveFromViewport();

	auto Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FInputModeGameOnly GameMode;
	Player->SetInputMode(GameMode);
	FSlateApplication::Get().SetAllUserFocusToGameViewport();
	Player->bShowMouseCursor = false;

	Cast<APuzzleManorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->SetInputEnabled(true);

	UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
}

void UWBadEnd::OnQuit()
{
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		GetPlayerContext().GetPlayerController(),
		EQuitPreference::Quit,
		true
	);
}
