// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickTrigger.h"

void UClickTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	auto Player = Cast<APuzzleManorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		Player->OnInteract.AddDynamic(this, &UClickTrigger::OnInteracted);
	}
}

void UClickTrigger::OnInteracted(AActor* ViewedActor)
{
	if (ViewedActor == GetOwner())
	{
		Trigger();
	}
}
