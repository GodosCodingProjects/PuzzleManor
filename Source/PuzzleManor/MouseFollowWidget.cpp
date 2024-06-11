// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseFollowWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"

void UMouseFollowWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Ticking Follow");

	if (!IsFollowing)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Ticking Success");

	float mouseX;
	float mouseY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);

	WidgetImage->GetPaintSpaceGeometry().GetAbsolutePosition();

	auto DPIScale = MyGeometry.GetLocalSize() / MyGeometry.GetAbsoluteSize();
	auto NewPos = FVector2D(mouseX, mouseY) * DPIScale;
	auto HalfSize = MyGeometry.GetLocalSize() / 2.0f;
		
	Cast<UCanvasPanelSlot>(Slot)->SetPosition(NewPos - HalfSize);
}