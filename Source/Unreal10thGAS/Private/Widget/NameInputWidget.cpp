// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NameInputWidget.h"
#include "Components/EditableTextBox.h"
#include "Framework/TestPlayerState.h"

void UNameInputWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NameInput)
	{
		NameInput->OnTextCommitted.AddDynamic(this, &UNameInputWidget::OnNameInputCommitted);
	}
}

void UNameInputWidget::OnNameInputCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod != ETextCommit::OnEnter) return;	// 엔터일때만 정상입력으로 처리

	if (ATestPlayerState* TestPS = GetOwningPlayerState<ATestPlayerState>())
	{
		TestPS->SetMyPlayerName(Text.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerState가 없습니다."));
	}
}
