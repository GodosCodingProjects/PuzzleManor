// Fill out your copyright notice in the Description page of Project Settings.


#include "WMenu.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleManorCharacter.h"

void UWMenu::OnWidgetRebuilt()
{
	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddUniqueDynamic(this, &UWMenu::OnResume);
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.AddUniqueDynamic(this, &UWMenu::OnRestart);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddUniqueDynamic(this, &UWMenu::OnQuit);
	}
}

void UWMenu::OnResume()
{
	Close();
}

void UWMenu::OnRestart()
{
	Close();

	UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
}

void UWMenu::OnQuit()
{
	UKismetSystemLibrary::QuitGame(
		GetWorld(), 
		GetPlayerContext().GetPlayerController(), 
		EQuitPreference::Quit, 
		true
	);
}

void UWMenu::Close()
{
	RemoveFromViewport();

	auto Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FInputModeGameOnly GameMode;
	Player->SetInputMode(GameMode);
	FSlateApplication::Get().SetAllUserFocusToGameViewport();
	Player->bShowMouseCursor = false;

	Cast<APuzzleManorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->SetInputEnabled(true);
}
