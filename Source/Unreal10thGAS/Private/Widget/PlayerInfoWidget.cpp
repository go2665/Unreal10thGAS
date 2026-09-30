// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerInfoWidget.h"
#include "Components/TextBlock.h"
#include "Framework/TestPlayerState.h"

void UPlayerInfoWidget::InitializePlayerStatBind(ATestPlayerState* InPS)
{
	if (InPS)
	{
		InPS->OnNameChanged.AddUObject(this, &UPlayerInfoWidget::UpdatePlayerName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerState가 없습니다."));
	}
}

void UPlayerInfoWidget::UpdatePlayerName(const FString & InName)
{
	PlayerName->SetText(FText::FromString(*InName));
}
