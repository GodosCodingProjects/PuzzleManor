// Fill out your copyright notice in the Description page of Project Settings.


#include "MapPin.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleManorCharacter.h"

// Sets default values
AMapPin::AMapPin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMapPin::OnInteract(AActor* ViewedActor, FVector ViewIntersection)
{
	if (ViewedActor == Cast<AActor>(this))
	{
		Pin->SetActorLocation(ViewIntersection);
	}
}

// Called when the game starts or when spawned
void AMapPin::BeginPlay()
{
	Super::BeginPlay();
	
	auto Player = Cast<APuzzleManorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		Player->OnInteract.AddUniqueDynamic(this, &AMapPin::OnInteract);
	}
}

