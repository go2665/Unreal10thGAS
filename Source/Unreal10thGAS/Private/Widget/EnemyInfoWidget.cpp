// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EnemyInfoWidget.h"
#include "Components/TextBlock.h"
#include "Framework/TestPlayerState.h"

void UEnemyInfoWidget::InitializePlayerStateBind(ATestPlayerState* InPS)
{
	if (InPS)
	{
		InPS->OnNameChanged.AddUObject(this, &UEnemyInfoWidget::UpdateEnemyName);
		InPS->OnScoreChanged.AddUObject(this, &UEnemyInfoWidget::UpdateEnemyScore);

		UpdateEnemyName(InPS->GetMyPlayerName());
		UpdateEnemyScore(InPS->GetMyPlayerScore());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerState가 없습니다."));
	}
}

void UEnemyInfoWidget::UpdateEnemyName(const FString& InName)
{
	EnemyName->SetText(FText::FromString(*InName));
}

void UEnemyInfoWidget::UpdateEnemyScore(int32 InScore)
{
	EnemyScore->SetText(FText::AsNumber(InScore));
}
