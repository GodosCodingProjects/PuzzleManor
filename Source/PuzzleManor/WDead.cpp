// Fill out your copyright notice in the Description page of Project Settings.


#include "WDead.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleManorCharacter.h"

void UWDead::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddUniqueDynamic(this, &UWDead::OnRestart);
	}
}

void UWDead::OnRestart()
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
