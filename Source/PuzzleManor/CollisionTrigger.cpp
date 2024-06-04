// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionTrigger.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void UCollisionTrigger::BeginPlay()
{
	Super::BeginPlay();

	auto Collision = GetOwner()->FindComponentByClass<UBoxComponent>();
	if (Collision)
	{
		Collision->OnComponentBeginOverlap.AddUniqueDynamic(this, &UCollisionTrigger::OnCollision);
	}
}

void UCollisionTrigger::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(TriggeringClass))
	{
		Trigger();
	}
}
