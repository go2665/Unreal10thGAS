// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NameplateWidget.h"
#include "Framework/TestPlayerState.h"
#include "Components/TextBlock.h"

void UNameplateWidget::InitializePlayerStateBind(ATestPlayerState* InPS)
{
	if (!InPS) return;
	InPS->OnNameChanged.AddUObject(this, &UNameplateWidget::UpdateName);
	UpdateName(InPS->GetMyPlayerName());

}

void UNameplateWidget::UpdateName(const FString & InName)
{
	NameText->SetText(FText::FromString(InName));
}
