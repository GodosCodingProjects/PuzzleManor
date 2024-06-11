// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickableWidget.h"

FReply UClickableWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	OnClickCompleted.Broadcast(this, InGeometry);
	return FReply::Unhandled();
}
