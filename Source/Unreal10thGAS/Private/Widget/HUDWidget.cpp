// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HUDWidget.h"
#include "Widget/StatWidget.h"
#include "Widget/PlayerInfoWidget.h"
#include "Widget/EnemyInfoWidget.h"
#include "Framework/TestPlayerState.h"
#include "Framework/TestGameState.h"
#include "Components/VerticalBox.h"
#include "TimerManager.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitGameStateBind();
}

void UHUDWidget::NativeDestruct()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle_InitGameState);

		if (ATestGameState* GS = World->GetGameState<ATestGameState>())
		{
			GS->OnPlayerStateAdded.RemoveAll(this);
			GS->OnPlayerStateRemoved.RemoveAll(this);
		}
	}

	EnemyWidgetMap.Empty();

	Super::NativeDestruct();
}

void UHUDWidget::InitGameStateBind()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	if (ATestGameState* GS = World->GetGameState<ATestGameState>())
	{
		GS->OnPlayerStateAdded.AddUObject(this, &UHUDWidget::OnPlayerStateAdded);
		GS->OnPlayerStateRemoved.AddUObject(this, &UHUDWidget::OnPlayerStateRemoved);

		// 이미 접속해 있는 기존 플레이어 목록 동기화
		for (APlayerState* ExistingPS : GS->PlayerArray)
		{
			OnPlayerStateAdded(ExistingPS);
		}

		World->GetTimerManager().ClearTimer(TimerHandle_InitGameState);
	}
	else
	{
		// GameState가 아직 리플리케이션되지 않았을 경우 재시도
		World->GetTimerManager().SetTimer(
			TimerHandle_InitGameState,
			this,
			&UHUDWidget::InitGameStateBind,
			0.1f,
			false
		);
	}
}

void UHUDWidget::InitializeWithAbilitySystem(AActor* InActor)
{
	if (StatWidget)
	{
		StatWidget->InitializeWithAbilitySystem(InActor);
	}
}

void UHUDWidget::InitializePlayerInfo(ATestPlayerState* InPS)
{
	LocalPlayerState = InPS;

	if (PlayerInfo)
	{
		PlayerInfo->InitializePlayerStateBind(InPS);
	}

	// 혹시 내 PlayerState가 타이밍 이슈로 EnemyInfoList에 추가되어 있다면 제거
	if (InPS)
	{
		OnPlayerStateRemoved(InPS);
	}
}

bool UHUDWidget::IsLocalPlayerState(APlayerState* InPS) const
{
	if (!InPS) return false;

	if (LocalPlayerState.IsValid() && LocalPlayerState.Get() == InPS)
	{
		return true;
	}

	if (const APlayerController* OwningPC = GetOwningPlayer())
	{
		if (OwningPC->PlayerState == InPS || InPS->GetPlayerController() == OwningPC)
		{
			return true;
		}
	}

	return false;
}

void UHUDWidget::OnPlayerStateAdded(APlayerState* InPS)
{
	if (!InPS) return;

	// 로컬 플레이어 본인이면 적 목록에 추가하지 않음
	if (IsLocalPlayerState(InPS)) return;

	// 이미 등록되어 있는지 확인
	if (EnemyWidgetMap.Contains(InPS)) return;

	if (!EnemyInfoList || !EnemyInfoWidgetClass) return;

	UEnemyInfoWidget* NewEnemyWidget = CreateWidget<UEnemyInfoWidget>(this, EnemyInfoWidgetClass);
	if (!NewEnemyWidget) return;

	EnemyInfoList->AddChildToVerticalBox(NewEnemyWidget);

	if (ATestPlayerState* TestPS = Cast<ATestPlayerState>(InPS))
	{
		NewEnemyWidget->InitializePlayerStateBind(TestPS);
	}

	EnemyWidgetMap.Add(InPS, NewEnemyWidget);
}

void UHUDWidget::OnPlayerStateRemoved(APlayerState* InPS)
{
	if (!InPS) return;

	if (TWeakObjectPtr<UEnemyInfoWidget>* FoundWidget = EnemyWidgetMap.Find(InPS))
	{
		if (FoundWidget->IsValid() && EnemyInfoList)
		{
			EnemyInfoList->RemoveChild(FoundWidget->Get());
		}
		EnemyWidgetMap.Remove(InPS);
	}
}

